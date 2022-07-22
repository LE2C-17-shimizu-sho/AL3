#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	// ���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = position;
	// ��]�p��ݒ�
	worldTransform_.rotation_ = rotation;

	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();

	// �V���O���C���X�^���X���擾����
	debugText_ = DebugText::GetInstance();
}

void RailCamera::Update() {
	using namespace MathUtility;
	
	// ���[���h�g�����X�t�H�[���̍��W�̐��l�����Z
	worldTransform_.translation_ += Vector3(0, 0, 0.1f);
	// ���[���h�g�����X�t�H�[�����X�V
	worldTransform_.matWorld_ = math::UpdateMatrix(worldTransform_);
	// ���[���h�s��̕��s�ړ��������擾
	viewProjection_.eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_.eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_.eye.z = worldTransform_.matWorld_.m[3][2];

	// ���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	// ���[���J�����̉�]�𔽉f
	forward = math::VecMatMul2(forward, worldTransform_.matWorld_);

	// ���_����O���ɓK���ȋ����i�񂾈ʒu�����ӓ_
	viewProjection_.target = viewProjection_.eye + forward;
	// ���[���h����x�N�g��
	Vector3 up(0, 1, 0);
	// ���[���J�����̉�]�𔽉f�i���[���J�����̏���x�N�g���j
	viewProjection_.up = math::VecMatMul2(up, worldTransform_.matWorld_);

	// �r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();

	// �f�o�b�N����
	debugText_->SetPos(20, 120);
	debugText_->GetInstance()->Printf(
		"RailCamera Pos:(%f,%f,%f)",
		viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z);
}



