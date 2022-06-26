#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;
	//	�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	velocity_ = velocity;
}

void PlayerBullet::Update(Affine* affine) {
	// ���W���ړ�������i1�t���[�����̈ړ��ʂ𑫂����ށj
	worldTransform_.translation_ += velocity_;

	// ���Ԍo�߂ŏ���
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollision() {
	isDead_ = true;
}