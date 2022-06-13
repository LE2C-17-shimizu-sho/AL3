#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);

	model_ = model;
	//	�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update(Affine* affine) {
	// ���W���ړ�������i1�t���[�����̈ړ��ʂɑ������ށj
	worldTransform_.translation_ += velocity_;

	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}