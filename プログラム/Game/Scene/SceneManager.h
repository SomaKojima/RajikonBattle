#pragma once

#include "../../StepTimer.h"
#include "../Utility/Singleton.h"
#include "../Object/GameObjectList.h"

/// <summary>
/// 前方宣言
/// </summary>
class Game;

/// <summary>
/// シーンクラス
/// </summary>
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	// 生成関数
	virtual void Instance() = 0;

	GameObjectList& GetGameObjectList() { return m_gameObjectList; }
protected:
	GameObjectList m_gameObjectList;
};

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager : public Singleton<SceneManager>
{
public:
	/// <summary>
	/// シーン判別ID
	/// </summary>
	enum SceneID
	{
		Logo,
		Title,
		Play,

		Max
	};

public:
	// コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsedTime);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();

	// 現在のシーンを初期化
	void Reset();

	// シーンのIDを変える
	void ChangeSceneID(SceneID sceneid) { m_changeSceneID = sceneid; }

	// シーンを変える処理
	void ChangeScene();

	// 現在のシーンのゲームオブジェクトリストを取得
	GameObjectList& GetGameObjectList() { return m_currentScene->GetGameObjectList(); }

private:
	// 現在のシーンID
	SceneID m_currentSceneID;
	// 変えるときに使用する次のシーンのID
	SceneID m_changeSceneID;
	// 現在のシーン
	Scene* m_currentScene;
};
