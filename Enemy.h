#pragma once
#include "WorldTransform.h"
#include "input.h"
#include "Model.h"
#include "DebugText.h"
#include <assert.h>
#include <memory.h>
#include <List>
#include "MathUtility.h"

#include "Affine.h"
#include "EnemyBullet.h"

using namespace MathUtility;

/// <summary>
///  ���@�N���X�̑O���錾
/// </summary>
class Player;

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


	/// <summary>
	/// �G�̐ڋ�
	/// </summary>
	void ApproechMove();

	/// <summary>
	/// �G�̗��E
	/// </summary>
	void LeaveMove();

	/// <summary>
	/// �e����
	/// </summary>
	void Fire();

	/// <summary>
	/// �ڋ߃t�F�[�Y�̏�����
	/// </summary>
	void ApproschInitislize();

	/// <summary>
	/// �����x�N�g��
	/// </summary>
	const void VecDifference();

public:
	// ���ˊԊu
	static int const kFireInterbal = 60;

	// �Z�b�^�[
	void SetPlayer(Player* player) { player_ = player; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
	// ���L����
	Player* player_ = nullptr;

	// �e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// �s���t�F�[�Y
	enum class Phase {
		Approach,	// �ڋ߂���
		Leave,		// ���E����
	};

	// �t�F�[�Y
	Phase phase_ = Phase::Approach;

	// ���˃^�C�}�[
	int32_t fireTimer = 0;
};

