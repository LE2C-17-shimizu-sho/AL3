#include "Enemy.h"
#include "Player.h"

void Enemy::Initailize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	//	�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("enemy.png");

	debugText_ = DebugText::GetInstance();

	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	ApproschInitislize();
}

void Enemy::OnCollision(){}

void Enemy::ApproschInitislize() {
	// ���˃^�C�}�[�̏�����
	fireTimer = kFireInterbal;
}

Vector3 Enemy::GetWorldPosition() {
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::ApproechMove() {
	// ���x�ݒ�
	Vector3 approchMove;
	const float enemySpeed = 0.2f;
	approchMove = { 0,0,-enemySpeed };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += approchMove;
	// �K��̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}

	// ���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	// �w�莞�ԂɒB����
	if (fireTimer < 0) {
		// �e�𔭎�
		Fire();
		// ���˃^�C�}�[��������
		fireTimer = kFireInterbal;
	}

	debugText_->SetPos(50, 100);
	debugText_->GetInstance()->Printf(
		"fierTimer:(%f)", fireTimer
	);
}

void Enemy::LeaveMove() {
	// ���x�ݒ�
	Vector3 leaveMove;
	const float enemySpeed = 0.2f;
	leaveMove = { -0.1f,0.1f,-enemySpeed };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += leaveMove;
}

void Enemy::Fire() {
	assert(player_);

	// ���L�����̍��W���R�s�[
	const float kBulletSpeed = 1.0f;

	// ���L�����̃��[���h���W���擾����
	Vector3 playerPos = player_->GetWorldPosition();
	// �G�L�����̃��[���h���W���擾����
	Vector3 enemyPos = GetWorldPosition();
	// �����x�N�g��
	Vector3 velocity =  playerPos - enemyPos;
	// ���K��
	velocity = MathUtility::Vector3Normalize(velocity);
	// �x�N�g���̒������A�����ɍ��킹��
	velocity *=  -kBulletSpeed;

	// �e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique <EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
}

void Enemy::Update() {

	// switch���Ńt�F�[�Y����
	switch (phase_) {
	case Phase::Approach:
	default:
		ApproechMove();
		//Fire();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	}


	// ���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.matWorld_ = math::UpdateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��

	// �f�o�b�N����
	debugText_->SetPos(50, 40);
	debugText_->GetInstance()->Printf(
		"Enemy(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}