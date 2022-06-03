#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"

class Affine
{
public:
#pragma region �x���@
	/// <summary>
	/// �x��
	/// </summary>
	float DegreeMethod(const float& degree);
#pragma endregion

#pragma region �A�t�B���ϊ��錾
	/// <summary>
	/// �X�P�[�����O
	/// </summary>
	Matrix4 Scaling(Vector3 scale);

	/// <summary>
	/// ��]Z
	/// </summary>
	Matrix4 RotationZ(float angle);

	/// <summary>
	/// ��]X
	/// </summary>
	Matrix4 RotationX(float angle);
	
	/// <summary>
	/// ��]Y
	/// </summary>
	Matrix4 RotationY(float angle);

	/// <summary>
	/// ���s�ړ�
	/// </summary>
	Matrix4 Translation(Vector3 translation);

	/// <summary>
	/// ���[���h�s��̌v�Z
	/// </summary>
	Matrix4 CreateMatrix(const WorldTransform& worldTransform);

	/// <summary>
	/// 1���̃��[���h�g�����X�t�H�[���X�V�֐�
	/// </summary>
	void WorldTransUpdate(WorldTransform& childWorldtrans);

	/// <summary>
	/// �����`�悷�邽�߂�for���X�V����
	/// </summary>
	void OrderUpdate();
#pragma endregion
};

