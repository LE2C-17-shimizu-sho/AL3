#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <assert.h>
#include "Affine.h"

/// <summary>
/// �G
/// </summary>
class Enemy
{
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initailize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="affine">�A�t�B���ϊ�</param>
	void Update(Affine* affine);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);

private:

	/// <summary>
	/// �G�̈ړ�
	/// </summary>
	void Move();

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ���x
	Vector3 velocity_;
};

