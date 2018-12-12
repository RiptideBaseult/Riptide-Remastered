#pragma once

#include "../../Engine/Engine.h"

class CMisc
{
public:
//[swap_lines]
	void OnRender();
	void OnEvents(IGameEvent * pEvent);
	void OnCreateMove( CUserCmd* cmd );
	void OnDrawModelExecute();
	void OnPlaySound( const char* pszSoundName );

	void OnOverrideView( CViewSetup* pSetup );
	void OnGetViewModelFOV( float& fov );

	void FrameStageNotify(ClientFrameStage_t Stage);

	vector<int> GetObservervators( int playerId );
	void OnRenderSpectatorList();

};
