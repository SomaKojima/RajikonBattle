
// デバッグ用ボックス情報

static const int VERTEX_CNT = 8;

static const DirectX::XMFLOAT3 vertexes[VERTEX_CNT] =
{
    { -1.0f,  1.0f, -1.0f },
    {  1.0f,  1.0f, -1.0f },
    {  1.0f,  1.0f,  1.0f },
    { -1.0f,  1.0f,  1.0f },
    { -1.0f, -1.0f, -1.0f },
    {  1.0f, -1.0f, -1.0f },
    {  1.0f, -1.0f,  1.0f },
    { -1.0f, -1.0f,  1.0f },
};

static const int INDEX_CNT = 24;

static const UINT indexes[INDEX_CNT] =
{
    0, 1, 1, 2, 2, 3, 3, 0,
	4, 5, 5, 6, 6, 7, 7, 4,
	0, 4, 1, 5, 2, 6, 3, 7
};



