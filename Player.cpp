#include "Player.h"

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

void Player::Move(Affine* affine) {

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

	// ���L�����̐���
	if (input_->PushKey(DIK_J)) {
		worldTransform_.rotation_.y -= 0.5f;
	}
	else if (input_->PushKey(DIK_K)) {
		worldTransform_.rotation_.y += 0.5f;
	}

	// �ړ����E���W
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 18;

	// �͈͂𒴂��Ȃ����� worldTransform_.translation_�l�ɐ�����`����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_ += move;
	worldTransform_.matWorld_ = affine->CreateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {

		// �e�𐶐����A������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// �e��o�^����
		bullet_ = newBullet;
	}
}

void Player::Update(Affine* affine) {
	// �L�����N�^�[�ړ��E���񏈗�
	Move(affine);

	// �L�����N�^�[�U������
	Attack();

	// �e�X�V
	if (bullet_) { // if (bullet_ != nullptr)
		bullet_->Update(affine);
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
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

