#include "Player.h"

/// <summary>
/// �x�N�g���ƍs��̊|���Z
/// </summary>
/// <param name="vec">�x�N�g��</param>
/// <param name="mat">�s��</param>
/// <returns>�x�N�g���ƍs��̊|���Z</returns>
Vector3 VecMatMul(Vector3& vec, Matrix4& mat) {
	Vector3 retVec = {};

	retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0];

	retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1];

	retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2];

	return retVec;
}

void Player::Initailize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
}

void Player::Move() {

	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,0 };

	// �L�����N�^�[�̈ړ�����
	const float kCharacterSpeed = 0.2f;

	// �L�[�{�[�h���͂ɂ��ړ�����
	// ���ړ�(�����������ňړ��x�N�g����ύX)
	if (input_->PushKey(DIK_LEFT)) {
		move = { -kCharacterSpeed,0,0 };
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move = { kCharacterSpeed,0,0 };
	}

	// �㉺�ړ�(�����������ňړ��x�N�g����ύX)
	if (input_->PushKey(DIK_UP)) {
		move = { 0, kCharacterSpeed,0 };
	}
	else if (input_->PushKey(DIK_DOWN)) {
		move = { 0, -kCharacterSpeed,0 };
	}

	worldTransform_.translation_ += move;
}

void Player::ScreenOut() {

	// �ړ����E���W
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 18;

	// �͈͂𒴂��Ȃ����� worldTransform_.translation_�l�ɐ�����`����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

void Player::Rotate() {

	const float roataionSpeed = 0.05f;

	// ���L�����̐���
	if (input_->PushKey(DIK_J)) {
		worldTransform_.rotation_.y -= roataionSpeed;
	}
	else if (input_->PushKey(DIK_K)) {
		worldTransform_.rotation_.y += roataionSpeed;
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {

		// ���L�����̍��W���R�s�[
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0,0,kBulletSpeed);

		// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = VecMatMul(velocity, worldTransform_.matWorld_);

		// �e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique <PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Update(Affine* affine) {
	// �L�����N�^�[�ړ�����
	Move();
	// �L�����N�^�[���񏈗�
	Rotate();

	// �ړ����E
	ScreenOut();

	// ���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��

	// �L�����N�^�[�U������
	Attack();

	// �e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { // if (bullet_ != nullptr)
		bullet->Update(affine);
	}

	// �f�o�b�N����
	debugText_->SetPos(50, 150);
	debugText_->GetInstance()->Printf(
		"Player(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// �e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { // if (bullet_ != nullptr)
		bullet->Draw(viewProjection);
	}
}

