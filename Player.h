#pragma once
#include "WorldTransform.h"
#include "input.h"
#include "Model.h"
#include "DebugText.h"
#include <assert.h>
#include "Affine.h"
#include "WinApp.h"

/// <summary>
/// ���L����
/// </summary>
class Player
{
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initailize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Affine* createMatrix);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection_">�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	void Draw(ViewProjection &viewProjection_);

	/// <summary>
	/// �v���C���[�̈ړ�
	/// </summary>
	/// <param name="createMatrix">�s��X�V</param>
	void Move(Affine* createMatrix);
private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// ���͏���
	Input* input_ = nullptr;
	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
};

