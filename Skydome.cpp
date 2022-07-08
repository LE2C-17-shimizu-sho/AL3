#include "Skydome.h"

void Skydome::Initialize(Affine* affine) {
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	// �X�P�[����ݒ�
	worldTransform_.scale_ = { 250.0f,250.0f,250.0f };
	// �X�P�[�����O�s��
	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
	// �s��̓]��
	worldTransform_.TransferMatrix();

	model_ =  Model::CreateFromOBJ("skydome", true);
}

void Skydome::Update() {}

void Skydome::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
