#include "Affine.h"
#include "Matrix4.h"
#include <math.h>
#include "WorldTransform.h"

const float PI = 3.141592654f;

/// <summary>
/// �x���@
/// </summary>
/// <param name="degree">�x���̎w��</param>
/// <returns>���̒l</returns>
float Affine::DegreeMethod(const float& degree) {
	float radian = degree * PI / 180.0f;
	return radian;
}

/// <summary>
/// �P�ʍs���ݒ�
/// </summary>
/// <returns>�P�ʍs��</returns>
Matrix4 Identity() {
	// �P�ʍs���ݒ�
	Matrix4 matIdentity;
	matIdentity.m[0][0] = 1.0f;
	matIdentity.m[1][1] = 1.0f;
	matIdentity.m[2][2] = 1.0f;
	matIdentity.m[3][3] = 1.0f;

	return matIdentity;
}

/// <summary>
/// �X�P�[�����O�s���ݒ�
/// </summary>
/// <param name="scaleX">�X�P�[��X</param>
/// <param name="scaleY">�X�P�[��Y</param>
/// <param name="scaleZ">�X�P�[��Z</param>
/// <returns>�X�P�[�����O�s��</returns>
Matrix4 Affine::Scaling(Vector3 scale) {
	Matrix4 matScale;
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
	matScale.m[3][3] = 1.0f;

	return matScale;
}

/// <summary>
/// Z���̉�]�s���ݒ�
/// </summary>
/// <param name="angle">= 1.0</param>
/// <returns>Z���̉�]�s��</returns>
Matrix4 Affine::RotationZ(float angle) {
	Matrix4 matRotZ;
	matRotZ.m[0][0] = cosf(angle);
	matRotZ.m[0][1] = sinf(angle);

	matRotZ.m[1][1] = cosf(angle);
	matRotZ.m[1][0] = -sinf(angle);

	matRotZ.m[2][2] = 1.0f;
	matRotZ.m[3][3] = 1.0f;

	return matRotZ;
}

/// <summary>
/// X���̉�]�s���ݒ�
/// </summary>
/// <param name="angle"></param>
/// <returns>X���̉�]�s��</returns>
Matrix4 Affine::RotationX(float angle) {
	Matrix4 matRotX;
	matRotX.m[1][1] = cosf(angle);
	matRotX.m[1][2] = sinf(angle);

	matRotX.m[2][1] = -sinf(angle);
	matRotX.m[2][2] = cosf(angle);

	matRotX.m[0][0] = 1.0f;

	matRotX.m[3][3] = 1.0f;

	return matRotX;
}

/// <summary>
/// Y���̉�]�s���ݒ�
/// </summary>
/// <param name="angle"></param>
/// <returns>Y���̉�]�s��</returns>
Matrix4 Affine::RotationY(float angle) {
	Matrix4 matRotY;
	matRotY.m[0][0] = cosf(angle);
	matRotY.m[0][2] = -sinf(angle);

	matRotY.m[2][0] = sinf(angle);
	matRotY.m[2][2] = cosf(angle);

	matRotY.m[1][1] = 1.0f;
	matRotY.m[3][3] = 1.0f;

	return matRotY;
}

/// <summary>
/// ���s�ړ��s���ݒ�
/// </summary>
/// <param name="tranlationX">���s�ړ�X</param>
/// <param name="tranlationY">���s�ړ�Y</param>
/// <param name="tranlationZ">���s�ړ�Z</param>
/// <returns>���s�ړ��s��</returns>
Matrix4 Affine::Translation(Vector3 translation) {
	Matrix4 matTrans;
	//�P�ʍs�����
	matTrans = Identity();

	matTrans.m[3][0] = translation.x;
	matTrans.m[3][1] = translation.y;
	matTrans.m[3][2] = translation.z;

	return matTrans;
}

/// <summary>
/// ���[���h�s��̌v�Z(�Q�Ɠn��)
/// </summary>
/// <param name="worldTransform">�X�P�[��, ��], ���s�ړ�</param>
/// <returns>���[���h�s��</returns>
Matrix4 Affine::CreateMatrix(const WorldTransform& worldTransform) {
	Matrix4 matWorld;

	matWorld = Identity();
	matWorld *= Scaling(worldTransform.scale_);
	matWorld *= RotationZ(worldTransform.rotation_.z);
	matWorld *= RotationX(worldTransform.rotation_.x);
	matWorld *= RotationY(worldTransform.rotation_.y);
	matWorld *= Translation(worldTransform.translation_);

	return matWorld;
}

/// <summary>
/// 1���̃��[���h�g�����X�t�H�[���X�V�֐�
/// </summary>
/// <param name="childWorldtrans">�q��worldTransform</param>
void Affine::WorldTransUpdate(WorldTransform& childWorldtrans) {
	childWorldtrans.matWorld_ = CreateMatrix(childWorldtrans); // ���������s��̌v�Z
	childWorldtrans.matWorld_ *= childWorldtrans.parent_->matWorld_; // parent_�̃��[���h�s��̊|���Z���
	childWorldtrans.TransferMatrix(); // �s��̓]��
}
