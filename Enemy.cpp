#include "Enemy.h"

void Enemy::Initailize(Model* model, const Vector3& position) {
	assert(model);

	model_ = model;
	//	�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("enemy.png");

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

void Enemy::Move() {
	Vector3 move;
	const float enemySpeed = 0.5f;
	move = { 0,0,-enemySpeed };

	worldTransform_.translation_ += move;
}

void Enemy::Update(Affine* affine) {
	// ���W���ړ�������i1�t���[�����̈ړ��ʂ𑫂����ށj
	worldTransform_.translation_ += velocity_;

	// �ړ�����
	Move();

	// ���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}