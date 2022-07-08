#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Affine.h"
#include <memory>
#include <cassert>

class Skydome
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Affine* affine);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
};

