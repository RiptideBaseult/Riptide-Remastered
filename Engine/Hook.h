#pragma once

#include "Engine.h"
namespace Engine
{
	namespace Hook
	{
		bool Initialize();
		void Shutdown();

		extern vfunc_hook surfaceCursor;
		extern vfunc_hook panel;
		extern vfunc_hook client;
		extern vfunc_hook clientmode;
		extern vfunc_hook eventmanager;
		extern vfunc_hook device;

		using FrameStageNotify = void(__thiscall*)(IBaseClientDLL*, ClientFrameStage_t);
		using CreateMove = void(__thiscall *)(IClientMode*, float flInputSampleTime, CUserCmd* pCmd);
		using GameEvent = bool(__thiscall*)(void*, IGameEvent*);
		using ResetHook = void(__thiscall *)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
		using DrawModelExecute = void(__thiscall*)(IVModelRender*, IMatRenderContext*, const DrawModelState_t&, const ModelRenderInfo_t&, matrix3x4_t*);
		typedef void(__thiscall* LockCursor)(void*);
		using ModelRender = void(__thiscall *)(IVModelRender* fix, IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld);
	}
}