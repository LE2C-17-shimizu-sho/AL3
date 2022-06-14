#include "Enemy.h"

void Enemy::Initailize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	//	�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("enemy.png");

	debugText_ = DebugText::GetInstance();

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
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
}

void Enemy::LeaveMove() {
	// ���x�ݒ�
	Vector3 leaveMove;
	const float enemySpeed = 0.2f;
	leaveMove = { -0.1f,0.1f,-enemySpeed };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += leaveMove;
}

void Enemy::Update(Affine* affine) {
	// switch���Ńt�F�[�Y����
	switch (phase_) {
	case Phase::Approach:
	default:
		ApproechMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	}

	// ���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
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