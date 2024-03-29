#pragma once

class Offsets {

public:
    Offsets();
    static int LocalPlayer;
    static int HudInstance;
    static int HudInstanceWorldMousePos;

    static int HeroInterface;

    static int ViewProjMatrices;
    static int GameTime;
    static int ObjectManager;
    static int Renderer;
    static int MissileInterface;
    static int MinionInterface;
    static int TurretInterface;
    static int InhibitorInterface;
    static int BuildingInterface;
    static int oGetHPBarPos;
    static int AINetClient;
    static int CpuInstance;
    static int MinimapObject;
    static int MinimapObjectHud;
    static int MinimapHudPos;
    static int MinimapHudSize;
    static int Chat;
    static int ChatIsOpen;
    static int ObjBuffManager;
    static int BuffManagerEntriesArray;
    static int BuffManagerEndArray;
    static int BuffHash;
    static int BuffEntryBuff;
    static int BuffType;
    static int BuffEntryBuffStartTime;
    static int BuffEntryBuffEndTime;
    static int BuffEntryBuffCount;
    static int BuffEntryBuffCountAlt;
    static int BuffEntryBuffCountAlt2;
    static int BuffName;
    static int BuffName2;
    static int BuffEntryBuffNodeStart;
    static int BuffEntryBuffNodeCurrent;
    static int OMissileObjectEntry;
    static int OMissileSpellInfo;
    static int OMissileSrcIdx;
    static int OMissileDestIdx;
    static int OMissileStartPos;
    static int OMissileEndPos;
    static int OMissileCurrentPos;
    static int OSpellInfoSlot;
    static int OSpellInfoData;
    static int OSpellInfoStartTime;
    static int OSpellInfoIndex;
    static int OSpellInfoLevel;
    static int OSpellInfoName;
    static int OSpellInfoDataName;
    static int AIManager;
    static int AIManagerStartPath;
    static int AIManagerEndPath;
    static int AIManagerClickRightPosition;
    static int AIManagerCastPosition;
    static int AIManagerIsMoving;
    static int AIManagerOwnPosition;
    static int AIManagerMoveSpeed;
    static int AIManagerServPosition;
    static int AIManagerIsDashing;
    static int AIManagerDashpeed;
    static int AIManagerVelocity;
    static int AIManagerNavigationArray;
    static int AIManagerNavigationArrayLength;
    static int AIManagerPosition;
    static int AIManagerNavGrid;
    static int AIManagerCurrentSegment;
    static int SpellSlotLevel;

    static int SpellInfoSpellName;

    static int ActiveSpell;
    static int ActiveSpellStartPos;
    static int ActiveSpellEndPos;
    static int ActiveSpellInfo;
    static int ActiveSpellName;
    static int ActiveSpellCastTime;
    static int ActiveSpellEndTime;

    static int SpellSlotTime;
    static int SpellSlotCharges;
    static int SpellSlotTimeCharge;
    static int SpellSlotDamage;
    static int SpellSlotSpellInfo;
    static int SpellInfoSpellData;
    static int SpellDataSpellName;
    static int SpellDataMissileName;
    static int SpellSlotSmiteTimer;
    static int SpellSlotSmiteCharges;
    static int SpellSlotItemMaxStackCount;
    static int SpellSlotItemNextRefillTime;
    static int SpellSlotItemStackState;
    static int SpellSlotItemActiveState;
    static int SpellSlotItemCooldown;
    static int SpellSlotItemTargetIngClient;
    static int SpellSlotItemName;
    static int SpellBOOKActiveSpellCast;
    static int SpellBOOKSpellSlots;
    static int ObjIndex;
    static int ObjTeam;
    static int ObjMissileName;
    static int ObjNetWorkId;
    static int ObjPos;
    static int ObjMissileSpellCast;
    static int ObjVisibility;
    static int ObjSpawnCount;
    static int ObjSrcIndex;
    static int ObjMana;
    static int ObjMaxMana;
    static int ObjAmmo;
    static int ObjMaxAmmo;
    static int ObjRecallName;
    static int ObjRecallState;
    static int ObjDead;
    static int ObjHealth;
    static int ObjHPBarPos;
    static int ObjMaxHealth;
    static int ObjAbilityHaste;
    static int ObjMagicPenFlat;
    static int ObjAbilityPower;
    static int ObjMagicPen;
    static int ObjMagicPenMulti;
    static int ObjArmorPen;
    static int ObjMagicPenMod;
    static int ObjLethality;
    static int ObjArmor;
    static int ObjBonusArmor;
    static int ObjMagicRES;
    static int ObjBonusMagicRES;
    static int ObjBaseATK;
    static int ObjBonusATK;
    static int ObjBonusAP;
    static int ObjBonusAPMOD;
    static int ObjATTACKSPEEDMOD;
    static int ObjMOVESPEED;
    static int ObjSpellBOOK;
    static int ObjSpellBOK2;
    static int ObjTRANSFORMATION;
    static int ObjName;
    static int ObjLVL;
    static int ObjSIZEMULTIPLIER;
    static int ObjEXPIRY;
    static int ObjCritMOD;
    static int ObjCrit;
    static int ObjCritMULTI;
    static int ObjATKSpeedMulti;
    static int ObjATKRange;
    static int ObjTargetable;
    static int ObjInvulnerable;
    static int ObjIsMoving;
    static int ObjDirection;
    static int ObjItemList;
    static int ObjExperience;
    static int ObjAdditionalAPMulti;
    static int ObjManaRegen;
    static int ObjHealthRegen;
    static int ObjercentArmorPen;
    static int ObjPercentMagicPen;
    static int ObjLifeSteal;
    static int ObjCritChance;
    static int ObjIsZombie;
    static int ObjIsOnScreen;
    static int ObjActionState;
    ////CHARDATA///
    static int ObjPreCharData;
    static int ObjCharData;
    static int ObjSelectionRadius;
    static int ObjBoundingRadius;
    static int ObjBaseMoveSpeed;
    static int ObjBaseMana;
    static int ObjBaseHealth;

    static int RendererWidth;
    static int RendererHeight;

    // functions
    static int CollisionFlag;
};