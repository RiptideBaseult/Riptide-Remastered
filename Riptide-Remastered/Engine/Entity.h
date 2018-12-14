#pragma once

#include "Engine.h"

namespace Engine
{
	class CBaseWeapon;
	class CBaseViewModel;

	class CBaseEntity : public IClientEntity
	{
	public:
		//[swap_lines]
		char*	GetPlayerName();

		bool	IsPlayer();
		bool	IsValid();
		bool	IsDead();
		Vector GetOrigin();
		Vector * GetVAngles();
		bool	IsVisible(CBaseEntity* pLocalEntity);
		int		GetMoveType();
		bool	HasHelmet();
		bool	HasDefuser();
		int    IsDefusing();
		int		IsFlashed();
		bool*	IsSpotted();

		int		GetFovStart();
		int		GetFlags();
		int		GetHealth();
		int		GetArmor();
		int		GetTeam();
		float   GetLowerBodyYaw();
		float   GetSimTime();
		float   GetFlashDuration();
		int		GetShotsFired();
		int		GetIsScoped();
		int		GetTickBase();
		float m_hGroundEntity();
		int movetype();
		float m_nWaterLevel();
		ObserverMode_t GetObserverMode();
		PVOID GetObserverTarget();

		PVOID			GetActiveWeapon();
		CBaseWeapon*	GetBaseWeapon();
		UINT*			GetWeapons();
		UINT*			GetWearables();
		CBaseViewModel* GetViewModel();

		Vector	GetAimPunchAngle();
		Vector	GetViewPunchAngle();

		Vector	GetVelocity();
		Vector	GetViewOffset();
		Vector	GetEyePosition();

		QAngle	GetEyeAngles();

		Vector	GetBonePosition(int nBone);
		Vector	GetHitboxPosition(int nHitbox);

		studiohdr_t* GetStudioModel();

		mstudiobone_t* GetBone(int nBone);
		mstudiobbox_t* GetHitBox(int nHitbox);

		mstudiohitboxset_t* GetHitBoxSet();
		//[/swap_lines]
	};

	class CBaseViewModel : public IClientEntity
	{
	public:
		//[swap_lines]
		int		GetModelIndex();
		void	SetModelIndex(int nModelIndex);
		void	SetWeaponModel(const char* Filename, IClientEntity* Weapon);

		DWORD	GetOwner();
		DWORD	GetWeapon();
		//[/swap_lines]
	};

	enum PLAYER_TEAM
	{
		TEAM_SPEC = 1,
		TEAM_TT,
		TEAM_CT
	};

	enum class CLIENT_CLASS_ID
	{
		ClassId_CAI_BaseNPC = 0,
		CAK47,
		CBaseAnimating,
		ClassId_CBaseAnimatingOverlay,
		ClassId_CBaseAttributableItem,
		ClassId_CBaseButton,
		CBaseCombatCharacter,
		CBaseCombatWeapon,
		CBaseCSGrenade,
		ClassId_CBaseCSGrenadeProjectile,
		ClassId_CBaseDoor,
		ClassId_CBaseEntityXXXXX, //EDITED
		ClassId_CBaseFlex,
		CBaseGrenade,
		ClassId_CBaseParticleEntity,
		CBasePlayer,
		ClassId_CBasePropDoor,
		ClassId_CBaseTeamObjectiveResource,
		ClassId_CBaseTempEntity,
		ClassId_CBaseToggle,
		ClassId_CBaseTrigger,
		ClassId_CBaseViewModelXXXXXXXXXXXXXX,//EDITED
		ClassId_CBaseVPhysicsTrigger,
		ClassId_CBaseWeaponWorldModel,
		ClassId_CBeam,
		ClassId_CBeamSpotlight,
		ClassId_CBoneFollower,
		ClassId_CBRC4Target,
		ClassId_CBreachCharge,
		ClassId_CBreachChargeProjectile,
		ClassId_CBreakableProp,
		ClassId_CBreakableSurface,
		CC4,
		ClassId_CCascadeLight,
		CChicken,
		ClassId_CColorCorrection,
		ClassId_CColorCorrectionVolume,
		ClassId_CCSGameRulesProxy,
		CCSPlayer,
		ClassId_CCSPlayerResource,
		ClassId_CCSRagdoll,
		CCSTeam,
		ClassId_CDangerZone,
		ClassId_CDangerZoneController,
		CDEagle,
		CDecoyGrenade,
		CDecoyProjectile,
		ClassId_CDrone,
		ClassId_CDronegun,
		ClassId_CDynamicLight,
		ClassId_CDynamicProp,
		ClassId_CEconEntity,
		CEconWearable,
		ClassId_CEmbers,
		ClassId_CEntityDissolve,
		ClassId_CEntityFlame,
		ClassId_CEntityFreezing,
		ClassId_CEntityParticleTrail,
		ClassId_CEnvAmbientLight,
		ClassId_CEnvDetailController,
		ClassId_CEnvDOFController,
		ClassId_CEnvGasCanister,
		ClassId_CEnvParticleScript,
		ClassId_CEnvProjectedTexture,
		ClassId_CEnvQuadraticBeam,
		ClassId_CEnvScreenEffect,
		ClassId_CEnvScreenOverlay,
		ClassId_CEnvTonemapController,
		ClassId_CEnvWind,
		ClassId_CFEPlayerDecal,
		ClassId_CFireCrackerBlast,
		ClassId_CFireSmoke,
		ClassId_CFireTrail,
		CFish,
		ClassId_CFists,
		ClassId_CFlashbang,
		ClassId_CFogController,
		ClassId_CFootstepControl,
		ClassId_CFunc_Dust,
		ClassId_CFunc_LOD,
		ClassId_CFuncAreaPortalWindow,
		ClassId_CFuncBrush,
		ClassId_CFuncConveyor,
		ClassId_CFuncLadder,
		ClassId_CFuncMonitor,
		ClassId_CFuncMoveLinear,
		ClassId_CFuncOccluder,
		ClassId_CFuncReflectiveGlass,
		ClassId_CFuncRotating,
		ClassId_CFuncSmokeVolume,
		ClassId_CFuncTrackTrain,
		ClassId_CGameRulesProxy,
		ClassId_CGrassBurn,
		ClassId_CHandleTest,
		CHEGrenade,
		ClassId_CHostage,
		ClassId_CHostageCarriableProp,
		ClassId_CIncendiaryGrenade,
		ClassId_CInferno,
		ClassId_CInfoLadderDismount,
		ClassId_CInfoMapRegion,
		ClassId_CInfoOverlayAccessor,
		ClassId_CItem_Healthshot,
		ClassId_CItemCash,
		ClassId_CItemDogtags,
		CKnife,
		CKnifeGG,
		ClassId_CLightGlow,
		ClassId_CMaterialModifyControl,
		ClassId_CMelee,
		CMolotovGrenade,
		CMolotovProjectile,
		ClassId_CMovieDisplay,
		ClassId_CParadropChopper,
		ClassId_CParticleFire,
		ClassId_CParticlePerformanceMonitor,
		ClassId_CParticleSystem,
		ClassId_CPhysBox,
		ClassId_CPhysBoxMultiplayer,
		ClassId_CPhysicsProp,
		ClassId_CPhysicsPropMultiplayer,
		ClassId_CPhysMagnet,
		ClassId_CPhysPropAmmoBox,
		ClassId_CPhysPropLootCrate,
		ClassId_CPhysPropRadarJammer,
		ClassId_CPhysPropWeaponUpgrade,
		CPlantedC4,
		ClassId_CPlasma,
		ClassId_CPlayerResource,
		ClassId_CPointCamera,
		ClassId_CPointCommentaryNode,
		ClassId_CPointWorldText,
		ClassId_CPoseController,
		ClassId_CPostProcessController,
		ClassId_CPrecipitation,
		ClassId_CPrecipitationBlocker,
		ClassId_CPredictedViewModel,
		ClassId_CProp_Hallucination,
		ClassId_CPropCounter,
		ClassId_CPropDoorRotating,
		ClassId_CPropJeep,
		ClassId_CPropVehicleDriveable,
		ClassId_CRagdollManager,
		ClassId_CRagdollProp,
		ClassId_CRagdollPropAttached,
		ClassId_CRopeKeyframe,
		CSCAR17,
		ClassId_CSceneEntity,
		ClassId_CSensorGrenade,
		ClassId_CSensorGrenadeProjectile,
		ClassId_CShadowControl,
		ClassId_CSlideshowDisplay,
		CSmokeGrenade,
		CSmokeGrenadeProjectile,
		CSmokeStack,
		ClassId_CSpatialEntity,
		ClassId_CSpotlightEnd,
		ClassId_CSprite,
		ClassId_CSpriteOriented,
		ClassId_CSpriteTrail,
		ClassId_CStatueProp,
		ClassId_CSteamJet,
		ClassId_CSun,
		ClassId_CSunlightShadowControl,
		ClassId_CSurvivalSpawnChopper,
		ClassId_CTablet,
		ClassId_CTeam,
		ClassId_CTeamplayRoundBasedRulesProxy,
		ClassId_CTEArmorRicochet,
		ClassId_CTEBaseBeam,
		ClassId_CTEBeamEntPoint,
		ClassId_CTEBeamEnts,
		ClassId_CTEBeamFollow,
		ClassId_CTEBeamLaser,
		ClassId_CTEBeamPoints,
		ClassId_CTEBeamRing,
		ClassId_CTEBeamRingPoint,
		ClassId_CTEBeamSpline,
		ClassId_CTEBloodSprite,
		ClassId_CTEBloodStream,
		ClassId_CTEBreakModel,
		ClassId_CTEBSPDecal,
		ClassId_CTEBubbles,
		ClassId_CTEBubbleTrail,
		ClassId_CTEClientProjectile,
		ClassId_CTEDecal,
		ClassId_CTEDust,
		ClassId_CTEDynamicLight,
		ClassId_CTEEffectDispatch,
		ClassId_CTEEnergySplash,
		ClassId_CTEExplosion,
		ClassId_CTEFireBullets,
		ClassId_CTEFizz,
		ClassId_CTEFootprintDecal,
		ClassId_CTEFoundryHelpers,
		ClassId_CTEGaussExplosion,
		ClassId_CTEGlowSprite,
		ClassId_CTEImpact,
		ClassId_CTEKillPlayerAttachments,
		ClassId_CTELargeFunnel,
		ClassId_CTEMetalSparks,
		ClassId_CTEMuzzleFlash,
		ClassId_CTEParticleSystem,
		ClassId_CTEPhysicsProp,
		CTEPlantBomb,
		ClassId_CTEPlayerAnimEvent,
		ClassId_CTEPlayerDecal,
		ClassId_CTEProjectedDecal,
		ClassId_CTERadioIcon,
		ClassId_CTEShatterSurface,
		ClassId_CTEShowLine,
		ClassId_CTesla,
		CTESmoke,
		ClassId_CTESparks,
		ClassId_CTESprite,
		ClassId_CTESpriteSpray,
		ClassId_CTest_ProxyToggle_Networkable,
		ClassId_CTestTraceline,
		ClassId_CTEWorldDecal,
		ClassId_CTriggerPlayerMovement,
		ClassId_CTriggerSoundOperator,
		ClassId_CVGuiScreen,
		ClassId_CVoteController,
		ClassId_CWaterBullet,
		ClassId_CWaterLODControl,
		CWeaponAug,
		CWeaponAWP,
		CWeaponBaseItem,
		CWeaponBizon,
		CWeaponCSBase,
		CWeaponCSBaseGun,
		ClassId_CWeaponCycler,
		CWeaponElite,
		CWeaponFamas,
		CWeaponFiveSeven,
		CWeaponG3SG1,
		CWeaponGalil,
		CWeaponGalilAR,
		CWeaponGlock,
		CWeaponHKP2000,
		CWeaponM249,
		CWeaponM3,
		CWeaponM4A1,
		CWeaponMAC10,
		CWeaponMag7,
		CWeaponMP5Navy,
		CWeaponMP7,
		CWeaponMP9,
		CWeaponNegev,
		CWeaponNOVA,
		CWeaponP228,
		CWeaponP250,
		CWeaponP90,
		CWeaponSawedoff,
		CWeaponSCAR20,
		CWeaponScout,
		CWeaponSG550,
		CWeaponSG552,
		CWeaponSG556,
		CWeaponSSG08,
		CWeaponTaser,
		CWeaponTec9,
		CWeaponTMP,
		CWeaponUMP45,
		CWeaponUSP,
		CWeaponXM1014,
		CWorld,
		CWorldVguiText,
		DustTrail,
		ClassId_MovieExplosion,
		ClassId_ParticleSmokeGrenade,
		ClassId_RocketTrail,
		ClassId_SmokeTrail,
		ClassId_SporeExplosion,
		ClassId_SporeTrail,
		MAX_CLASSID
	};
}