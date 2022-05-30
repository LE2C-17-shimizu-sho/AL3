#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "TextureManager.h"

/// <summary>
/// ���L����
/// </summary>
class Player
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHnadle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model,uint32_t textureHnadle);

	/// <summary>
	/// �X�V
	/// </summary>
	void update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// ���L����
	Player* player_ = nullptr;
};

