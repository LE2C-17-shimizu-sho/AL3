#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MathUtility.h"
#include "DebugText.h"
#include "Affine.h"

/// <summary>
/// ���[���J����
/// </summary>
class RailCamera
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	RailCamera() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~RailCamera() = default;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="position">�������W</param>
	/// <param name="rotation">�����p�x</param>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �r���[�v���W�F�N�V�������擾
	/// </summary>
	/// <returns>�r���[�v���W�F�N�V����</returns>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	// ���[���h�s����擾
	WorldTransform* GetWorldMatirx() { return &worldTransform_; }



private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = DebugText::GetInstance();
};

