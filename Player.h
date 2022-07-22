#pragma once
#include "WorldTransform.h"
#include "input.h"
#include "Model.h"
#include "DebugText.h"
#include <assert.h>
#include <memory.h>
#include <List>

#include "Affine.h"
#include "PlayerBullet.h"

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
	void Initailize(Model* model, uint32_t textureHandle, WorldTransform* parent, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection_">�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	void Draw(ViewProjection &viewProjection_);

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	/// <summary>
	/// �ړ����E���W
	/// </summary>
	void ScreenOut();

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փˎ��R�[���o�b�N���Ăяo��
	void OnCollision();

	// �e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

private:

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
		
	/// <summary>
	/// ���񏈗�
	/// </summary>
	void Rotate();

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

	// �e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};

