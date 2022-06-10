#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"
#include <math.h>

class Affine
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Affine() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Affine() = default;
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
	/// 
	/// </summary>
	/// <param name="angle"></param>
	/// <returns></returns>
	Matrix4 RotationY(float angle);

	/// <summary>
	/// ���s�ړ�
	/// </summary>
	/// <param name="translation">���s�ړ�</param>
	/// <returns></returns>
	Matrix4 Translation(Vector3 translation);

	/// <summary>
	/// ���[���h�s��̌v�Z
	/// </summary>
	/// <param name="worldTransform">���[���h�g�����X�t�H�[��</param>
	/// <returns></returns>
	Matrix4 CreateMatrix(const WorldTransform& worldTransform);

	/// <summary>
	/// 1���̃��[���h�g�����X�t�H�[���X�V�֐�
	/// </summary>
	void WorldTransUpdate(WorldTransform& childWorldtrans);
#pragma endregion
};

