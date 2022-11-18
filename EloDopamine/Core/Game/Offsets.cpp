#include "Offsets.h"

//"version": "12.21.4770420+branch.releases-12-21.content.release"
Offsets::Offsets() {};

//== HUD ==//
int Offsets::HudInstance = 0x18a6fa4; // 8B ? ? ? ? ? 6A 00 8B ? ? E8 ? ? ? ? B0 01 ?
int Offsets::HudInstanceWorldMousePos = 0x19C;
//==RENDERER==//
int Offsets::RendererWidth = 0x8;
int Offsets::RendererHeight = 0xc;
//== CORE ==//
int	Offsets::ViewProjMatrices = 0x31696A0; //68 ? ? ? ? 51 8B 00
int Offsets::LocalPlayer = 0x3143DA0; //57 8B 3D ? ? ? ? 3B F7 75
int Offsets::GameTime = 0x313D244; //F3 0F 11 05 ? ? ? ? 8B 49
int Offsets::ObjectManager = 0x18A6ED8; //89 ? ? ? ? ? 57 C7 06 ? ? ? ? 66 C7 46 04 ? ?
int Offsets::Renderer = 0x316EE68; //8B 0D ? ? ? ? 50 E8 ? ? ? ? 5E 8B // A1 ?? ?? ?? ?? 56 57 BF ?? ?? ?? ?? 8B
//== LISTS ==//
int	Offsets::MissileInterface = 0x3143DF0; //8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 30 8B 36
int	Offsets::MinionInterface = 0x24F45E0; //8B 0D ? ? ? ? E8 ? ? ? ? EB 09 // A3 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 04 85 C0 74 32
int	Offsets::TurretInterface = 0x313BA44; //8B 35 ? ? ? ? 8B 76 18 // 8D 44 24 0C 89 35 ? ? ? ? // A1 ? ? ? ? 53 56 8B 70 04
int	Offsets::InhibitorInterface = 0x3143EFC; //A1 ?? ?? ?? ?? 53 55 56 8B 70 04 8B 40 08
int	Offsets::HeroInterface = 0x18A6F70; //89 44 24 18 A1 ? ? ? ? 53 // 8B 15 ? ? ? ? 0F 44 C1
int	Offsets::BuildingInterface = 0x1859378;
int	Offsets::oGetHPBarPos = 0x30C9;  //E8 ?? ?? ?? ?? 8B 4E ?? 8D 54 ?? ?? 52 8B 01 FF ?? ?? 5E 83 ?? ?? C3
int	Offsets::AINetClient = 0x314868C; //8B 0D ?? ?? ?? ?? 85 C9 74 06 8B 01 6A 01 FF 10 8B 0D ?? ?? ?? ?? C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 85 C9 74 06 8B 01 6A 01 FF 10 C3 //C7 05 ? ? ? ? ? ? ? ? 85 C9 74 06 8B 01 6A 01 FF 10 C3 - //A1 ?? ?? ?? ?? 88 4C 24 13
int	Offsets::CpuInstance = AINetClient - 0x3C;
//== MINIMAP STRUCTURE ==//
int	Offsets::MinimapObject = 0x313D288; //8B 1D ? ? ? ? 85 DB 74 19 //74 22 8B 0D ? ? ? ? 85 C9 74 18 80 79 38 00
int	Offsets::MinimapObjectHud = 0x150;  //C7 44 24 ? ? ? ? ? E8 ? ? ? ? 8B B7 ? ? ? ? 8B //Tomar primer valor ejemplo [esp+120h+var_D4]
int	Offsets::MinimapHudPos = 0x3C;
int	Offsets::MinimapHudSize = 0x44;
//== CHAT STRUCTURE ==//
int	Offsets::Chat = 0x3143E4C; //8B 0D ? ? ? ? 8A D8 85 // 8B 0D ? ? ? ? 8A D8 85 C9 //8B 0D ? ? ? ? 83 78 44 00
int	Offsets::ChatIsOpen = 0x6D8; //C7 86 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 04 85 C0 75 30 F6 86 ? ? ? ? ? 75 1B 38 86 ? ? ? ?
//== BUFF MANAGER STRUCTURE ==//
int	Offsets::ObjBuffManager = 0x2330; //8D 83 ? ? ? ? 50 8D AB ? ? ? ? // //8b 81 ? ? ? ? 81 c1 ? ? ? ? 8b 40 0c ff e0 cc // 4 first characters are the offset
int	Offsets::BuffManagerEntriesArray = 0x10;
int	Offsets::BuffManagerEndArray = 0x14;
int	Offsets::BuffHash = 0x88;
int	Offsets::BuffEntryBuff = 0x8;
int	Offsets::BuffType = 0x4;
int	Offsets::BuffEntryBuffStartTime = 0xC;
int	Offsets::BuffEntryBuffEndTime = 0x10;
int	Offsets::BuffEntryBuffCount = 0x74;
int	Offsets::BuffEntryBuffCountAlt = 0x24;
int	Offsets::BuffEntryBuffCountAlt2 = 0x28;
int	Offsets::BuffName = 0x8;
int	Offsets::BuffName2 = 0x4;
int	Offsets::BuffEntryBuffNodeStart = 0x20;
int	Offsets::BuffEntryBuffNodeCurrent = 0x24;
//== Missile LIST ==//
int	Offsets::OMissileObjectEntry = 0x14;
int	Offsets::OMissileSpellInfo = 0x0260;
int	Offsets::OMissileSrcIdx = 0x2C4;
int	Offsets::OMissileDestIdx = 0x31C; // - At first Position
int	Offsets::OMissileStartPos = 0x2E0;
int Offsets::OMissileCurrentPos = 0x1DC;
int	Offsets::OMissileEndPos = 0x2EC;
int	Offsets::OSpellInfoSlot = 0x4;
int	Offsets::OSpellInfoData = 0x40;
int	Offsets::OSpellInfoStartTime = 0x8;
int	Offsets::OSpellInfoIndex = 0xC;
int	Offsets::OSpellInfoLevel = 0x58;
int	Offsets::OSpellInfoName = 0x104;
int	Offsets::OSpellInfoDataName = 0x6C;
//== AI MANAGER STRUCTURE ==//
int	Offsets::AIManager = 0x2E84; //LPLAYER->VTABLE 149 MOV
int	Offsets::AIManagerStartPath = 0x1CC;
int	Offsets::AIManagerEndPath = 0x1D8;
int	Offsets::AIManagerServPosition = 0x2EC;
int	Offsets::AIManagerVelocity = 0x2F8;
int	Offsets::AIManagerIsMoving = 0x1C0;
int	Offsets::AIManagerCurrentSegment = 0x1C4;
int	Offsets::AIManagerIsDashing = 0x214;  //controlar con Ghost Spell
int	Offsets::AIManagerDashpeed = 0x1F8; //Ghost Spell . si no viene el speed is not dashing
int	Offsets::AIManagerNavigationArray = 0x1E4;
int	Offsets::AIManagerNavigationArrayLength = 0x1E8;
int	Offsets::AIManagerMoveSpeed = 0x1BC;
int	Offsets::AIManagerClickRightPosition = 0x10;
int	Offsets::AIManagerCastPosition = 0x388;
int	Offsets::AIManagerOwnPosition = 0x3E4;
int	Offsets::AIManagerPosition = 0x2EC;
int	Offsets::AIManagerNavGrid = 0x1B0;


//== Spell STRUCTURE ==//
int	Offsets::SpellSlotLevel = 0x1C;
int	Offsets::SpellSlotTime = 0x24;
int	Offsets::SpellSlotCharges = 0x58;
int	Offsets::SpellSlotTimeCharge = 0x78;
int	Offsets::SpellSlotDamage = 0x94;
int	Offsets::SpellSlotSpellInfo = 0x120;
int Offsets::SpellInfoSpellName = 0x18;
int	Offsets::SpellInfoSpellData = 0x44;
int	Offsets::SpellDataSpellName = 0x6C;
int	Offsets::SpellDataMissileName = 0x6C;
int	Offsets::SpellSlotSmiteTimer = 0x64;
int	Offsets::SpellSlotSmiteCharges = 0x58;
int	Offsets::SpellSlotItemMaxStackCount = 0x6;
int	Offsets::SpellSlotItemNextRefillTime = 0x6;
int	Offsets::SpellSlotItemStackState = 0x7;
int	Offsets::SpellSlotItemActiveState = 0x7;
int	Offsets::SpellSlotItemCooldown = 0x7;
int	Offsets::SpellSlotItemTargetIngClient = 0x13;
int	Offsets::SpellSlotItemName = 0x13;
int	Offsets::SpellBOOKActiveSpellCast = 0x20;  //always the same
int	Offsets::SpellBOOKSpellSlots = 0x488; //always the same

//== FUNCTIONS ==//
int Offsets::CollisionFlag = 0x18a722c; // E8 ? ? ? ? 55 8A D8

//== ObjECT ATTRIBUTES ==//
int	Offsets::ObjIndex = 0x8;
int	Offsets::ObjTeam = 0x34;
int	Offsets::ObjMissileName = 0x54;
int	Offsets::ObjNetWorkId = 0xB4;
int	Offsets::ObjPos = 0x1DC;
int	Offsets::ObjMissileSpellCast = 0x250;
int	Offsets::ObjVisibility = 0x274;
int	Offsets::ObjSpawnCount = 0x288;
int	Offsets::ObjSrcIndex = 0x294;
int	Offsets::ObjMana = 0x29C;
int	Offsets::ObjMaxMana = 0x2AC;
int	Offsets::ObjAmmo = 0x030C;
int	Offsets::ObjMaxAmmo = ObjAmmo + 0x10;
int	Offsets::ObjRecallName = 0xD60;
int	Offsets::ObjRecallState = 0xD90;  //ObjRECALLName + 0x10
int	Offsets::ObjDead = 0x021C; // Real Dead offset - 0x4
int	Offsets::ObjHealth = 0xE74;
int	Offsets::ObjHPBarPos = 0x136C;
int	Offsets::ObjMaxHealth = 0xE84;
int	Offsets::ObjAbilityHaste = 0x16A0;
int	Offsets::ObjMagicPenFlat = 0x118C;
int	Offsets::ObjAbilityPower = 0x1750;
int	Offsets::ObjMagicPen = 0x1270;
int	Offsets::ObjMagicPenMulti = 0x1278;
int	Offsets::ObjArmorPen = ObjMagicPen + 0x4;
int	Offsets::ObjMagicPenMod = ObjMagicPen + 0x8;
int	Offsets::ObjLethality = 0x128c;
int	Offsets::ObjArmor = 0x137C;
int	Offsets::ObjBonusArmor = 0x1380;
int	Offsets::ObjMagicRES = 0x1384;
int	Offsets::ObjBonusMagicRES = 0x1388;
int	Offsets::ObjBaseATK = 0x1354;
int	Offsets::ObjBonusATK = 0x12CC;
int	Offsets::ObjBonusAP = ObjBonusATK + 0x10;
int	Offsets::ObjBonusAPMOD = ObjBonusAP + 0x4;
int	Offsets::ObjATTACKSPEEDMOD = 0x1268;
int	Offsets::ObjMOVESPEED = 0x1394;
int	Offsets::ObjSpellBOOK = 0x29C0; //8B 84 83 ? ? ? ? EB 06 8B 83 ? ? ? ? 85 C0 0F 84 ? ? ? ? 53 8B CF E8 ? ? ? ? 8B C8 8B 10 FF 52 18 8B F0
int	Offsets::ObjSpellBOK2 = 0x2518; //ObjSpellBOOK+0x20
int	Offsets::ObjTRANSFORMATION = 0x3040;
int	Offsets::ObjName = 0x2DAC;
int	Offsets::ObjLVL = 0x358C; // ó 0x353C
int	Offsets::ObjSIZEMULTIPLIER = 0x136C;
int	Offsets::ObjEXPIRY = 0x298;
int	Offsets::ObjCritMOD = ObjBaseATK + 0x10;
int	Offsets::ObjCrit = ObjCritMOD + 0x10;
int	Offsets::ObjCritMULTI = 0x12D0;
int	Offsets::ObjATKSpeedMulti = 0x1350; //F3 0F 10 80 ? ? ? ? F3 0F 11 ? ? 50 E8
int	Offsets::ObjATKRange = 0x139C; //D9 83 ? ? ? ? 5F 5E 5B 83 C4 08 C3
int	Offsets::ObjTargetable = 0xD04;
int	Offsets::ObjInvulnerable = 0x029C;
int	Offsets::ObjIsMoving = 0x32EF;
int	Offsets::ObjDirection = 0x1F4;
int	Offsets::ObjItemList = 0x33E8;
int	Offsets::ObjExperience = 0x357C;
int	Offsets::ObjAdditionalAPMulti = 0x1230;
int	Offsets::ObjManaRegen = 0x11E0;
int	Offsets::ObjHealthRegen = 0x1390;
int	Offsets::ObjercentArmorPen = 0x11E0;
int	Offsets::ObjPercentMagicPen = 0x11E4;
int	Offsets::ObjLifeSteal = 0x12A0;
int	Offsets::ObjCritChance = 0x12E0;
int	Offsets::ObjIsZombie = 0x3A;
int	Offsets::ObjIsOnScreen = 0x278;
int Offsets::ObjActionState = 0x1830;
////CHARDATA///
int	Offsets::ObjPreCharData = 0x2D20;
int	Offsets::ObjCharData = 0x1C;
int	Offsets::ObjSelectionRadius = 0x54C;
int	Offsets::ObjBoundingRadius = 0x458;
int	Offsets::ObjBaseMoveSpeed = 0x1C4;
int	Offsets::ObjBaseMana = 0xC8;
int	Offsets::ObjBaseHealth = 0x74;
