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

void Player::Move(Affine* createMatrix) {

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
		move = {0, kCharacterSpeed,0 };
	}
	else if (input_->PushKey(DIK_DOWN)) {
		move = { 0, -kCharacterSpeed,0 };
	}

	// �ړ����E���W
	const float kMoveLimitX = WinApp::kWindowWidth;
	const float kMoveLimitX = WinApp::kWindowHeight;

	worldTransform_.translation_ += move;
	worldTransform_.matWorld_ = createMatrix->CreateMatrix(worldTransform_);
	worldTransform_.TransferMatrix(); // �s��̓]��
}

void Player::Update(Affine* createMatrix) {
	Move(createMatrix);

	debugText_->SetPos(50, 150);
	debugText_->GetInstance()->Printf(
		"Player(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);
}

void Player::Draw(ViewProjection& viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

