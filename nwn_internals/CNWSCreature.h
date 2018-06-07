#ifndef _NX_NWN_STRUCT_CNWSCREATURE_
#define _NX_NWN_STRUCT_CNWSCREATURE_

#include "CExoArrayList_2.h"
#include "CAutoMap.h"
#include "CNWSCreatureAppearanceInfo.h"

struct CNWSCreature_s {
	CNWSObject							obj;
	uint32_t							spacer_01;//1C0
	uint32_t							spacer_02;
	uint32_t							spacer_03;
	uint32_t							spacer_04;
	uint32_t							spacer_05;
	uint32_t							spacer_06;
	uint32_t							spacer_07;
	uint32_t							spacer_08;
	uint32_t							spacer_09;
	uint32_t							spacer_10;
	uint32_t							spacer_11;
	uint32_t							spacer_12;
	uint32_t							spacer_13;
	CNWSCreatureEventHandler			cre_events;							/* 0x01F4 */  /* size: 104 (13*8 bytes) */
	uint32_t							spacer1[26];						/* 0x025C */
	CNWSQuickbarButton					*cre_quickbar;						/* 0x02C4 */
	uint32_t							cre_lootable;						/* 02C8 */
	uint32_t							cre_decaytime;						/* 02CC */
	uint32_t							cre_bodybag_id;						/* 02D0 */
	uint32_t							cre_area_id;
	float								cre_XPosition;
	float								cre_YPosition;
	float								cre_ZPosition;
	uint8_t								spacer2_017;
	uint8_t								spacer2_018;
	uint8_t								spacer2_019;
	uint8_t								spacer2_020;
	uint8_t								spacer2_021;
	uint8_t								spacer2_022;
	uint8_t								spacer2_023;
	uint8_t								spacer2_024;
	uint8_t								spacer2_025;
	uint8_t								spacer2_026;
	uint8_t								spacer2_027;
	uint8_t								spacer2_028;
	uint8_t								spacer2_029;
	uint8_t								spacer2_030;
	uint8_t								spacer2_031;
	uint8_t								spacer2_032;
	uint8_t								spacer2_033;
	uint8_t								spacer2_034;
	uint8_t								spacer2_035;
	uint8_t								spacer2_036;
	uint8_t								spacer2_037;
	uint8_t								spacer2_038;
	uint8_t								spacer2_039;
	uint8_t								spacer2_040;
	uint8_t								spacer2_041;
	uint8_t								spacer2_042;
	uint8_t								spacer2_043;
	uint8_t								spacer2_044;
	uint8_t								spacer2_045;
	uint8_t								spacer2_046;
	uint8_t								spacer2_047;
	uint8_t								spacer2_048;
	uint8_t								spacer2_049;
	uint8_t								spacer2_050;
	uint8_t								spacer2_051;
	uint8_t								spacer2_052;
	uint32_t							field_308;
    int32_t								m_bUpdateCombatInformation;
    int32_t								m_nNumCharSheetViewers;
    int32_t								m_bUpdateSpellSlots;
    int32_t								m_bOnCreationScriptExecuted;
	uint8_t								spacer2_073;
	uint8_t								spacer2_074;
	uint8_t								spacer2_075;
	uint8_t								spacer2_076;
	uint8_t								spacer2_077;
	uint8_t								spacer2_078;
	uint8_t								spacer2_079;
	uint8_t								spacer2_080;
	uint32_t							field_0324;
	uint32_t							field_0328;
	uint8_t								spacer2_089;
	uint8_t								spacer2_090;
	uint8_t								spacer2_091;
	uint8_t								spacer2_092;
	uint8_t								spacer2_093;
	uint8_t								spacer2_094;
	uint8_t								spacer2_095;
	uint8_t								spacer2_096;
	uint8_t								spacer2_097;
	uint8_t								spacer2_098;
	uint8_t								spacer2_099;
	uint8_t								spacer2_100;
	uint8_t								spacer2_101;
	uint8_t								spacer2_102;
	uint8_t								spacer2_103;
	uint8_t								spacer2_104;
	uint8_t								spacer2_105;
	uint8_t								spacer2_106;
	uint8_t								spacer2_107;
	uint8_t								spacer2_108;
	uint32_t							cre_exciteduration;
	uint8_t								spacer2_113;
	uint8_t								spacer2_114;
	uint8_t								spacer2_115;
	uint8_t								spacer2_116;
	uint8_t								spacer2_117;
	uint8_t								spacer2_118;
	uint8_t								spacer2_119;
	uint8_t								spacer2_120;
	uint8_t								spacer2_121;
	uint8_t								spacer2_122;
	uint8_t								spacer2_123;
	uint8_t								spacer2_124;
	uint8_t								spacer2_125;
	uint8_t								spacer2_126;
	uint8_t								spacer2_127;
	uint8_t								spacer2_128;
	uint8_t								spacer2_129;
	uint8_t								spacer2_130;
	uint8_t								spacer2_131;
	uint8_t								spacer2_132;
	uint8_t								spacer2_133;
	uint8_t								spacer2_134;
	uint8_t								spacer2_135;
	uint8_t								spacer2_136;
	uint8_t								spacer2_137;
	uint8_t								spacer2_138;
	uint8_t								spacer2_139;
	uint8_t								spacer2_140;
	uint8_t								spacer2_141;
	uint8_t								spacer2_142;
	uint8_t								spacer2_143;
	uint8_t								spacer2_144;
	uint8_t								spacer2_145;
	uint8_t								spacer2_146;
	uint8_t								spacer2_147;
	uint8_t								spacer2_148;
	uint8_t								spacer2_149;
	uint8_t								spacer2_150;
	uint8_t								spacer2_151;
	uint8_t								spacer2_152;
	uint8_t								spacer2_153;
	uint8_t								spacer2_154;
	uint8_t								spacer2_155;
	uint8_t								spacer2_156;
	uint8_t								spacer2_157;
	uint8_t								spacer2_158;
	uint8_t								spacer2_159;
	uint8_t								spacer2_160;
	uint8_t								spacer2_161;
	uint8_t								spacer2_162;
	uint8_t								spacer2_163;
	uint8_t								spacer2_164;
	uint8_t								spacer2_165;
	uint8_t								spacer2_166;
	uint8_t								spacer2_167;
	uint8_t								spacer2_168;
	uint8_t								spacer2_169;
	uint8_t								spacer2_170;
	uint8_t								spacer2_171;
	uint8_t								spacer2_172;
	uint8_t								spacer2_173;
	uint8_t								spacer2_174;
	uint8_t								spacer2_175;
	uint8_t								spacer2_176;
	uint8_t								spacer2_177;
	uint8_t								spacer2_178;
	uint8_t								spacer2_179;
	uint8_t								spacer2_180;
	uint8_t								spacer2_181;
	uint8_t								spacer2_182;
	uint8_t								spacer2_183;
	uint8_t								spacer2_184;
	uint8_t								spacer2_185;
	uint8_t								spacer2_186;
	uint8_t								spacer2_187;
	uint8_t								spacer2_188;
	uint8_t								spacer2_189;
	uint8_t								spacer2_190;
	uint8_t								spacer2_191;
	uint8_t								spacer2_192;
	uint8_t								spacer2_193;
	uint8_t								spacer2_194;
	uint8_t								spacer2_195;
	uint8_t								spacer2_196;
	uint8_t								spacer2_197;
	uint8_t								spacer2_198;
	uint8_t								spacer2_199;
	uint8_t								spacer2_200;
	uint8_t								spacer2_201;
	uint8_t								spacer2_202;
	uint8_t								spacer2_203;
	uint8_t								spacer2_204;
	uint8_t								spacer2_205;
	uint8_t								spacer2_206;
	uint8_t								spacer2_207;
	uint8_t								spacer2_208;
	uint8_t								spacer2_209;
	uint8_t								spacer2_210;
	uint8_t								spacer2_211;
	uint8_t								spacer2_212;
	uint8_t								spacer2_213;
	uint8_t								spacer2_214;
	uint8_t								spacer2_215;
	uint8_t								spacer2_216;
	uint8_t								spacer2_217;
	uint8_t								spacer2_218;
	uint8_t								spacer2_219;
	uint8_t								spacer2_220;
	uint8_t								spacer2_221;
	uint8_t								spacer2_222;
	uint8_t								spacer2_223;
	uint8_t								spacer2_224;
	uint8_t								spacer2_225;
	uint8_t								spacer2_226;
	uint8_t								spacer2_227;
	uint8_t								spacer2_228;
	uint8_t								spacer2_229;
	uint8_t								spacer2_230;
	uint8_t								spacer2_231;
	uint8_t								spacer2_232;
	uint8_t								spacer2_233;
	uint8_t								spacer2_234;//zrejme onspawn
	uint8_t								spacer2_235;
	uint8_t								spacer2_236;
	uint8_t								spacer2_237;
	uint8_t								spacer2_238;
	uint8_t								spacer2_239;
	uint8_t								spacer2_240;
	uint8_t								spacer2_241;
	uint8_t								spacer2_242;
	uint8_t								spacer2_243;
	uint8_t								spacer2_244;
	uint8_t								spacer2_245;
	uint8_t								spacer2_246;
	uint8_t								spacer2_247;
	uint8_t								spacer2_248;
	uint8_t								spacer2_249;
	uint8_t								spacer2_250;
	uint8_t								spacer2_251;
	uint8_t								spacer2_252;
	uint8_t								spacer2_253;
	uint8_t								spacer2_254;
	uint8_t								spacer2_255;
	uint8_t								spacer2_256;
	uint8_t								spacer2_257;
	uint8_t								spacer2_258;
	uint8_t								spacer2_259;
	uint8_t								spacer2_260;
	uint8_t								spacer2_261;
	uint8_t								spacer2_262;
	uint8_t								spacer2_263;
	uint8_t								spacer2_264;
	uint8_t								spacer2_265;
	uint8_t								spacer2_266;
	uint8_t								spacer2_267;
	uint8_t								spacer2_268;
	uint8_t								spacer2_269;
	uint8_t								spacer2_270;
	uint8_t								spacer2_271;
	uint8_t								spacer2_272;
	uint8_t								spacer2_273;
	uint8_t								spacer2_274;
	uint8_t								spacer2_275;
	uint8_t								spacer2_276;
	uint8_t								spacer2_277;
	uint8_t								spacer2_278;
	uint8_t								spacer2_279;
	uint8_t								spacer2_280;
	uint8_t								spacer2_281;
	uint8_t								spacer2_282;
	uint8_t								spacer2_283;
	uint8_t								spacer2_284;
	uint8_t								spacer2_285;
	uint8_t								spacer2_286;
	uint8_t								spacer2_287;
	uint8_t								spacer2_288;
	uint8_t								spacer2_289;
	uint8_t								spacer2_290;
	uint8_t								spacer2_291;
	uint8_t								spacer2_292;
	uint8_t								spacer2_293;
	uint8_t								spacer2_294;
	uint8_t								spacer2_295;
	uint8_t								spacer2_296;
	uint8_t								spacer2_297;
	uint8_t								spacer2_298;
	uint8_t								spacer2_299;
	uint8_t								spacer2_300;
	uint8_t								spacer2_301;
	uint8_t								spacer2_302;
	uint8_t								spacer2_303;
	uint8_t								spacer2_304;
	uint8_t								spacer2_305;
	uint8_t								spacer2_306;
	uint8_t								spacer2_307;
	uint8_t								spacer2_308;
	uint8_t								spacer2_309;
	uint8_t								spacer2_310;
	uint8_t								spacer2_311;
	uint8_t								spacer2_312;
	uint8_t								spacer2_313;
	uint8_t								spacer2_314;
	uint8_t								spacer2_315;
	uint8_t								spacer2_316;
	uint8_t								spacer2_317;
	uint8_t								spacer2_318;
	uint8_t								spacer2_319;
	uint8_t								spacer2_320;
	uint8_t								spacer2_321;
	uint8_t								spacer2_322;
	uint8_t								spacer2_323;
	uint8_t								spacer2_324;
	uint8_t								spacer2_325;
	uint8_t								spacer2_326;
	uint8_t								spacer2_327;
	uint8_t								spacer2_328;
	uint8_t								spacer2_329;
	uint8_t								spacer2_330;
	uint8_t								spacer2_331;
	uint8_t								spacer2_332;
	uint8_t								spacer2_333;
	uint8_t								spacer2_334;
	uint8_t								spacer2_335;
	uint8_t								spacer2_336;
	uint8_t								spacer2_337;
	uint8_t								spacer2_338;
	uint8_t								spacer2_339;
	uint8_t								spacer2_340;
	uint8_t								spacer2_341;
	uint8_t								spacer2_342;
	uint8_t								spacer2_343;
	uint8_t								spacer2_344;
	uint8_t								spacer2_345;
	uint8_t								spacer2_346;
	uint8_t								spacer2_347;
	uint8_t								spacer2_348;
	uint8_t								spacer2_349;
	uint8_t								spacer2_350;
	uint8_t								spacer2_351;
	uint8_t								spacer2_352;
	uint8_t								spacer2_353;
	uint8_t								spacer2_354;
	uint8_t								spacer2_355;
	uint8_t								spacer2_356;
	uint8_t								spacer2_357;
	uint8_t								spacer2_358;
	uint8_t								spacer2_359;
	uint8_t								spacer2_360;
	uint8_t								spacer2_361;
	uint8_t								spacer2_362;
	uint8_t								spacer2_363;
	uint8_t								spacer2_364;
	uint8_t								spacer2_365;
	uint8_t								spacer2_366;
	uint8_t								spacer2_367;
	uint8_t								spacer2_368;
	uint8_t								spacer2_369;
	uint8_t								spacer2_370;
	uint8_t								spacer2_371;
	uint8_t								spacer2_372;
	uint8_t								spacer2_373;
	uint8_t								spacer2_374;
	uint8_t								spacer2_375;
	uint8_t								spacer2_376;
	uint8_t								spacer2_377;
	uint8_t								spacer2_378;
	uint8_t								spacer2_379;
	uint8_t								spacer2_380;
	uint8_t								spacer2_381;
	uint8_t								spacer2_382;
	uint8_t								spacer2_383;
	uint8_t								spacer2_384;
	uint8_t								spacer2_385;
	uint8_t								spacer2_386;
	uint8_t								spacer2_387;
	uint8_t								spacer2_388;
	uint8_t								spacer2_389;
	uint8_t								spacer2_390;
	uint8_t								spacer2_391;
	uint8_t								spacer2_392;
	uint8_t								spacer2_393;
	uint8_t								spacer2_394;
	uint8_t								spacer2_395;
	uint8_t								spacer2_396;
	uint8_t								spacer2_397;
	uint8_t								spacer2_398;
	uint8_t								spacer2_399;
	uint8_t								spacer2_400;
	uint8_t								spacer2_401;
	uint8_t								spacer2_402;
	uint8_t								spacer2_403;
	uint8_t								spacer2_404;
	uint8_t								spacer2_405;
	uint8_t								spacer2_406;
	uint8_t								spacer2_407;
	uint8_t								spacer2_408;
	uint8_t								spacer2_409;
	uint8_t								spacer2_410;
	uint8_t								spacer2_411;
	uint8_t								spacer2_412;
	uint8_t								spacer2_413;
	uint8_t								spacer2_414;
	uint8_t								spacer2_415;
	uint8_t								spacer2_416;
	uint8_t								spacer2_417;
	uint8_t								spacer2_418;
	uint8_t								spacer2_419;
	uint8_t								spacer2_420;
	uint8_t								spacer2_421;
	uint8_t								spacer2_422;
	uint8_t								spacer2_423;
	uint8_t								spacer2_424;
	uint8_t								spacer2_425;
	uint8_t								spacer2_426;
	uint8_t								spacer2_427;
	uint8_t								spacer2_428;
	uint8_t								cre_AmbientAnimState;
	uint8_t								spacer2_430;
	uint8_t								spacer2_431;
	uint8_t								spacer2_432;
	uint8_t								spacer2_433;
	uint8_t								spacer2_434;
	uint8_t								spacer2_435;
	uint8_t								spacer2_436;
	CCreatureMaps						AreaData;
//	void								**cre_areaminimaps;					/* 0x048C */
//	nwn_objid_t							*cre_arealist;						/* 0x0490 */
//	uint32_t 							cre_areacount;						/* 0x0494 */
//	uint32_t 							cre_areaalloc;						/* 0x0498 */
//	uint32_t 							cre_minimapcount;					/* 0x049C */
	uint8_t								spacer2_461;						/* 0x04A0 */
	uint8_t								spacer2_462;
	uint8_t								spacer2_463;
	uint8_t								spacer2_464;
	uint8_t								spacer2_465;						/* 0x04A4 */
	uint8_t								spacer2_466;
	uint8_t								spacer2_467;
	uint8_t								spacer2_468;
	uint8_t								cre_mode_detect;					/* 0x04A8 */
	uint8_t								cre_mode_stealth;					/* 0x04A9 */
	uint8_t								cre_mode_defcast;					/* 0x04AA */
	uint8_t								cre_mode_combat;					/* 0x04AB */
	uint8_t								cre_mode_desired;					/* 0x04AC */
	uint8_t								field_4AD;
	uint8_t								field_4AE;
	uint8_t								field_4AF;
	nwn_objid_t							cre_counterspell_target;			/* 0x04B0 */
	uint8_t								cre_initiative_roll;				/* 0x04B4 */
	uint8_t								field_4B5;
	uint8_t								field_4B6;
	uint8_t								field_4B7;
	uint32_t							cre_initiative_expired;				/* 0x04B8 */
	uint32_t							cre_combat_state;					/* 0x04BC */
	uint32_t							cre_combat_state_timer;				/* 0x04C0 */
	uint32_t							cre_passive_attack_beh;				/* 0x04C4 */
	uint32_t							cre_has_arms;						/* 0x04C8 */
	uint32_t							cre_has_legs;						/* 0x04CC */
	uint32_t							cre_is_disarmable;					/* 0x04D0 */
	uint8_t								cre_size;							/* 0x04D4 */
	uint8_t								field_4D5;
	uint8_t								field_4D6;
	uint8_t								field_4D7;
	float								cre_pref_attack_dist;				/* 0x04D8 */
	float								cre_weapon_scale;					/* 0x04DC *///TODO bylo uint_32!! bacha
	uint32_t							cre_attack_target;					/* 0x04E0 */
	nwn_objid_t							cre_attempted_target;				/* 0x04E4 */
	uint32_t							field_4E8;
	uint32_t							field_4EC;
	uint32_t							field_4F0;
	nwn_objid_t							cre_attacker;						/* 04F4 */
	nwn_objid_t							cre_attempted_spell;				/* 04F8 */
	nwn_objid_t							cre_spell_target;					/* 04FC */
	uint32_t							cre_last_ammo_warning;				/* 0500 */
	uint32_t							field_504;
	uint32_t							field_508;
	nwn_objid_t							cre_broadcast_aoo_to;				/* 050C */
	uint32_t							field_510;
	uint32_t							cre_ext_combat_mode;				/* 0514 */
	int32_t								cre_eff_bon_amt[50];				/* 0518 */
	int32_t								cre_eff_pen_amt[50];				/* 05E0 */
	int32_t								cre_eff_bon_spid[50];				/* 06A8 */
	int32_t								cre_eff_pen_spid[50];				/* 0770 */
	int32_t								cre_eff_bon_obj[50];				/* 0838 */
	int32_t								cre_eff_pen_obj[50];				/* 0900 */
	uint32_t							cre_silent;							/* 09C8 */
	uint32_t							cre_hasted;							/* 09CC */
	uint32_t							cre_slowed;							/* 09D0 */
	uint32_t							cre_taunted;						/* 09D4 */
	uint32_t							cre_forced_walk;					/* 09D8 */
	uint8_t								cre_vision_type;					/* 09DC */
	uint8_t								cre_state;							/* 09DD */
	uint8_t								field_9DE;
	uint8_t								field_9DF;
	int32_t								effect_spell_id;//9E0
	uint8_t								field_9E4;
	uint8_t								field_9E5;
	uint8_t								field_9E6;
	uint8_t								field_9E7;
	uint8_t								field_9E8;
	uint8_t								field_9E9;
	uint8_t								field_9EA;
	uint8_t								field_9EB;
	uint8_t								field_9EC;
	uint8_t								field_9ED;
	uint8_t								field_9EE;
	uint8_t								field_9EF;
	uint32_t							field_9F0;
	uint8_t								field_9F4;
	uint8_t								field_9F5;
	uint8_t								field_9F6;
	uint8_t								field_9F7;
	uint8_t								field_9F8;
	uint8_t								field_9F9;
	uint8_t								field_9FA;
	uint8_t								field_9FB;
	uint8_t								field_9FC;
	uint8_t								field_9FD;
	uint8_t								field_9FE;
	uint8_t								field_9FF;
	uint8_t								field_A00;
	uint8_t								field_A01;
	uint8_t								field_A02;
	uint8_t								field_A03;
	uint8_t								field_A04;
	uint8_t								field_A05;
	uint8_t								field_A06;
	uint8_t								field_A07;
	uint8_t								field_A08;
	uint8_t								field_A09;
	uint8_t								field_A0A;
	uint8_t								field_A0B;
	uint8_t								field_A0C;
	uint8_t								field_A0D;
	uint8_t								field_A0E;
	uint8_t								field_A0F;
	uint8_t								field_A10;
	uint8_t								field_A11;
	uint8_t								field_A12;
	uint8_t								field_A13;
	uint8_t								field_A14;
	uint8_t								field_A15;
	uint8_t								field_A16;
	uint8_t								field_A17;
	float								cre_primary_range;
	uint8_t								field_A1C;
	uint8_t								field_A1D;
	uint8_t								field_A1E;
	uint8_t								field_A1F;
	float								cre_secondary_range;
	uint8_t								field_A24;
	uint8_t								field_A25;
	uint8_t								field_A26;
	uint8_t								field_A27;
	uint8_t								field_A28;
	uint8_t								field_A29;
	uint8_t								field_A2A;
	uint8_t								field_A2B;
	uint8_t								field_A2C;
	uint8_t								field_A2D;
	uint8_t								field_A2E;
	uint8_t								field_A2F;
	void								*cre_perception_list;
	uint8_t								field_A34;
	uint8_t								field_A35;
	uint8_t								field_A36;
	uint8_t								field_A37;
	uint8_t								field_A38;
	uint8_t								field_A39;
	uint8_t								field_A3A;
	uint8_t								field_A3B;
	uint8_t								field_A3C;
	uint8_t								field_A3D;
	uint8_t								field_A3E;
	uint8_t								field_A3F;
	uint8_t								field_A40;
	uint8_t								field_A41;
	uint8_t								field_A42;
	uint8_t								field_A43;
	uint8_t								field_A44;
	uint8_t								field_A45;
	uint8_t								field_A46;
	uint8_t								field_A47;
	uint8_t								field_A48;
	uint8_t								field_A49;
	uint8_t								field_A4A;
	uint8_t								field_A4B;
	uint8_t								field_A4C;
	uint8_t								field_A4D;
	uint8_t								field_A4E;
	uint8_t								field_A4F;
	uint32_t							field_A50;
	uint32_t							cre_counterspell_id;//A54;
	uint8_t								cre_counterspell_class;//A58;
	uint8_t								cre_counterspell_meta;//A59;
	uint8_t								cre_counterspell_domain;//A5A;
	uint8_t								field_A5B;
	uint32_t							field_A5C;//CExoArrayList_uint32 cre_spell_identified
	uint32_t							field_A60;
	uint32_t							field_A64;
	uint32_t							cre_item_spell_item;//A68
	uint32_t							cre_lastspellunreadied;//A6C
	uint32_t							cre_item_spell;//A70
	uint32_t							cre_item_spell_level;//A74
	uint32_t							cre_item_spell_aoo;//A78
	uint32_t							SitObject;
	uint8_t								field_A80;
	uint8_t								field_A81;
	uint8_t								field_A82;
	uint8_t								field_A83;
	uint8_t								field_A84;
	uint8_t								field_A85;
	uint8_t								field_A86;
	uint8_t								field_A87;
	uint8_t								field_A88;
	uint8_t								field_A89;
	uint8_t								field_A8A;
	uint8_t								field_A8B;
	uint8_t								field_A8C;
	uint8_t								field_A8D;
	uint8_t								field_A8E;
	uint8_t								field_A8F;
	uint8_t								field_A90;
	uint8_t								field_A91;
	uint8_t								field_A92;
	uint8_t								field_A93;
	uint8_t								field_A94;
	uint8_t								field_A95;
	uint8_t								field_A96;
	uint8_t								field_A97;
	uint8_t								field_A98;
	uint8_t								field_A99;
	uint8_t								field_A9A;
	uint8_t								field_A9B;
	uint8_t								field_A9C;
	uint8_t								field_A9D;
	uint8_t								field_A9E;
	uint8_t								field_A9F;
	int32_t								cre_tauntanimationplayed;
    uint32_t							m_nRestDurationPerHPGain;
    uint32_t							m_nRestHPToRecover;
    uint32_t							m_nRestDurationPerSpellLevelGain;
    uint32_t							m_nRestSpellLevelToRecover;
	uint32_t							cre_facing_done;//AB4
	DWORD								cre_unlmited_arrow;//field_AB8;
	DWORD								cre_unlmited_bolt;//field_ABC;
	DWORD								cre_unlmited_bullet;//field_AC0;
	uint32_t							*cre_skill_timer;
	CNWSCombatRound						*cre_combat_round;					/* 0x0AC8 */
	uint32_t							field_ACC;
	uint32_t							field_AD0;
	uint32_t							cre_gold;							/* 0x0AD4 */
	uint32_t							cre_is_pc;							/* 0x0AD8 */
	uint16_t							cre_soundset;						/* 0x0ADC */
	uint16_t							field_AE2;							/* 0x0ADE */
	uint32_t							cre_footstep;						/* 0x0AE0 */
	uint8_t								cre_bodybag;						/* 0x0AE4 */
	uint8_t								field_AE5;
	uint8_t								field_AE6;
	uint8_t								field_AE7;
	uint8_t								field_AE8;
	uint8_t								field_AE9;
	uint8_t								field_AEA;
	uint8_t								field_AEB;
	uint8_t								field_AEC;
	uint8_t								field_AED;
	uint8_t								field_AEE;
	uint8_t								field_AEF;
	uint8_t								field_AF0;
	uint8_t								field_AF1;
	uint8_t								field_AF2;
	uint8_t								field_AF3;
	uint8_t								cre_IsImmortal;
	uint8_t								field_AF5;
	uint8_t								field_AF6;
	uint8_t								field_AF7;
	uint8_t								cre_no_permadeath;
	uint8_t								field_AF9;
	uint8_t								field_AFA;
	uint8_t								field_AFB;
	CExoString							cre_DisplayName;
	int32_t				m_bUpdateDisplayName;//B04
    uint16_t			m_nAIState;//b08
    uint8_t				m_nAIStateAction;//b0A
    uint32_t			m_oidAIStateActee;//b0C
    uint8_t				m_nAIStateOutput;//b10
	uint32_t							cre_aistate_activities;
	uint32_t							cre_activity_locked;
	float				m_fMovementRateFactor;
    float				m_fDriveModeMoveFactor;
	uint32_t			field_B24;
	uint32_t			field_B28;
	uint32_t							field_B2C;
	uint32_t							cre_MasterID;//B30
	CExoArrayList_uint32				*cre_associates;//B34
	uint16_t							cre_associate_type;//B38
	uint16_t							field_B3A;
	uint32_t							cre_associate_command;//B3C
	uint32_t							cre_summoned_acomp;//B40
	uint32_t							cre_summoned_famil;//B44
	uint32_t							field_B48;
	uint8_t								field_B4C;
	uint8_t								field_B4D;
	uint8_t								field_B4E;
	uint8_t								field_B4F;
	uint8_t								field_B50;
	uint8_t								field_B51;
	uint8_t								field_B52;
	uint8_t								field_B53;
	uint8_t								field_B54;
	uint8_t								field_B55;
	uint8_t								field_B56;
	uint8_t								field_B57;
	uint8_t								field_B58;
	uint8_t								field_B59;
	uint8_t								field_B5A;
	uint8_t								field_B5B;
	uint32_t							cre_default_reputation;
	uint8_t								field_B60;
	uint8_t								field_B61;
	uint8_t								field_B62;
	uint8_t								field_B63;
	uint32_t							EncounterObject;
	uint8_t								field_B68;
	uint8_t								field_B69;
	uint8_t								field_B6A;
	uint8_t								field_B6B;
	CNWSInventory						*cre_equipment;						/* 0x0B6C */
	CItemRepository						*cre_inventory;						/* 0x0B70 */
	uint16_t							cre_inventory_index;				/* 0x0B74 */
	uint16_t							cre_container_index;				/* 0x0B76 */
	nwn_objid_t							cre_current_container;				/* 0x0B78 */
	uint32_t							cre_equipped_weight;				/* 0x0B7C */
	uint32_t							cre_calc_npc_weight;				/* 0x0B80 */
	uint32_t							cre_encumbrance_state;				/* 0x0B84 */
	uint32_t							cre_last_pickup_failed;				/* 0x0B88 */
	uint32_t							cre_total_weight;					/* 0x0B8C */
	uint32_t							cre_pm_itemlist;					/* 0x0B90 */
	uint8_t								spacer5_005;/* 0x0B94 */
	uint8_t								spacer5_006;/* 0x0B95 */
	uint8_t								spacer5_007;/* 0x0B96 */
	uint8_t								spacer5_008;/* 0x0B97 */
	uint8_t								spacer5_009;/* 0x0B98 */
	uint8_t								spacer5_010;/* 0x0B99 */
	uint8_t								spacer5_011;/* 0x0B9A */
	uint8_t								spacer5_012;/* 0x0B9B */
	uint8_t								spacer5_013;/* 0x0B9C */
	uint8_t								spacer5_014;/* 0x0B9D */
	uint8_t								spacer5_015;/* 0x0B9E */
	uint8_t								spacer5_016;/* 0x0B9F */
	uint8_t								spacer5_017;/* 0x0BA0 */
	uint8_t								spacer5_018;/* 0x0BA1 */
	uint8_t								spacer5_019;/* 0x0BA2 */
	uint8_t								spacer5_020;/* 0x0BA3 */
	uint8_t								spacer5_021;/* 0x0BA4 */
	uint8_t								spacer5_022;/* 0x0BA5 */
	uint8_t								spacer5_023;/* 0x0BA6 */
	uint8_t								spacer5_024;/* 0x0BA7 */
	uint8_t								spacer5_025;/* 0x0BA8 */
	uint8_t								spacer5_026;/* 0x0BA9 */
	uint8_t								spacer5_027;/* 0x0BAA */
	uint8_t								spacer5_028;/* 0x0BAB */
	uint8_t								spacer5_029;/* 0x0BAC */
	uint8_t								spacer5_030;/* 0x0BAD */
	uint8_t								spacer5_031;/* 0x0BAE */
	uint8_t								spacer5_032;/* 0x0BAF */
	uint8_t								spacer5_033;/* 0x0BB0 */
	uint8_t								spacer5_034;/* 0x0BB1 */
	uint8_t								spacer5_035;/* 0x0BB2 */
	uint8_t								spacer5_036;/* 0x0BB3 */
	uint8_t								spacer5_037;/* 0x0BB4 */
	uint8_t								spacer5_038;/* 0x0BB5 */
	uint8_t								spacer5_039;/* 0x0BB6 */
	uint8_t								spacer5_040;/* 0x0BB7 */
	uint8_t								spacer5_041;/* 0x0BB8 */
	uint8_t								spacer5_042;/* 0x0BB9 */
	uint8_t								spacer5_043;/* 0x0BBA */
	uint8_t								spacer5_044;/* 0x0BBB */
	uint8_t								spacer5_045;/* 0x0BBC */
	uint8_t								spacer5_046;/* 0x0BBD */
	uint8_t								spacer5_047;/* 0x0BBE */
	uint8_t								spacer5_048;/* 0x0BBF */
	uint8_t								spacer5_049;/* 0x0BC0 */
	uint8_t								spacer5_050;/* 0x0BC1 */
	uint8_t								spacer5_051;/* 0x0BC2 */
	uint8_t								spacer5_052;/* 0x0BC3 */
	uint8_t								spacer5_053;/* 0x0BC4 */
	uint8_t								spacer5_054;/* 0x0BC5 */
	uint8_t								spacer5_055;/* 0x0BC6 */
	uint8_t								spacer5_056;/* 0x0BC7 */
	uint8_t								spacer5_057;/* 0x0BC8 */
	uint8_t								spacer5_058;/* 0x0BC9 */
	uint8_t								spacer5_059;/* 0x0BCA */
	uint8_t								spacer5_060;/* 0x0BCB */
	uint8_t								spacer5_061;/* 0x0BCC */
	uint8_t								spacer5_062;/* 0x0BCD */
	uint8_t								spacer5_063;/* 0x0BCE */
	uint8_t								spacer5_064;/* 0x0BCF */
	uint8_t								spacer5_065;/* 0x0BD0 */
	uint8_t								spacer5_066;/* 0x0BD1 */
	uint8_t								spacer5_067;/* 0x0BD2 */
	uint8_t								spacer5_068;/* 0x0BD3 */
	uint8_t								spacer5_069;/* 0x0BD4 */
	uint8_t								spacer5_070;/* 0x0BD5 */
	uint8_t								spacer5_071;/* 0x0BD6 */
	uint8_t								spacer5_072;/* 0x0BD7 */
	uint8_t								cre_pm_portrait;/* 0x0BD8 */
	uint8_t								spacer5_074;/* 0x0BD9 */
	uint8_t								spacer5_075;/* 0x0BDA */
	uint8_t								spacer5_076;/* 0x0BDB */
	uint8_t								spacer5_077;/* 0x0BDC */
	uint8_t								spacer5_078;/* 0x0BDD */
	uint8_t								spacer5_079;/* 0x0BDE */
	uint8_t								spacer5_080;/* 0x0BDF */
	uint8_t								spacer5_081;/* 0x0BE0 */
	uint8_t								spacer5_082;/* 0x0BE1 */
	uint8_t								spacer5_083;/* 0x0BE2 */
	uint8_t								spacer5_084;/* 0x0BE3 */
	uint8_t								spacer5_085;/* 0x0BE4 */
	uint8_t								spacer5_086;/* 0x0BE5 */
	uint8_t								spacer5_087;/* 0x0BE6 */
	uint8_t								spacer5_088;/* 0x0BE7 */
	uint16_t 							cre_pm_PortraitId;/* 0x0BE8 */
	uint8_t								spacer5_091;/* 0x0BEA */
	uint8_t								spacer5_092;/* 0x0BEB */
	uint32_t							cre_pm_IsPolymorphed;/* 0x0BEC */
	uint16_t							cre_pm_Appearance;/* 0x0BF0 */
	uint8_t								cre_pm_PrePolySTR;/* 0x0BF2 */
	uint8_t								cre_pm_PrePolyCON;/* 0x0BF3 */
	uint8_t								cre_pm_PrePolyDEX;/* 0x0BF4 */
	uint8_t								spacer5_102;/* 0x0BF5 */
	uint16_t 							cre_pm_RacialType;/* 0x0BF6 */
	uint16_t 							cre_pm_PrePolyHP;/* 0x0BF8 */
	uint8_t								spacer5_107;/* 0x0BFA */
	uint8_t								spacer5_108;/* 0x0BFB */
	uint8_t								spacer5_109;/* 0x0BFC */
	uint8_t								spacer5_110;/* 0x0BFD */
	uint8_t								spacer5_111;/* 0x0BFE */
	uint8_t								spacer5_112;/* 0x0BFF */
	uint8_t								spacer5_113;/* 0x0C00 */
	uint8_t								spacer5_114;/* 0x0C01 */
	uint8_t								spacer5_115;/* 0x0C02 */
	uint8_t								spacer5_116;/* 0x0C03 */
	uint8_t								spacer5_117;/* 0x0C04 */
	uint8_t								spacer5_118;/* 0x0C05 */
	uint8_t								spacer5_119;/* 0x0C06 */
	uint8_t								spacer5_120;/* 0x0C07 */
	uint32_t 							cre_pm_ACBonus_lo;/* 0x0C08 */
	uint32_t 							cre_pm_ACBonus_hi;/* 0x0C0C */
	uint32_t 							cre_pm_HPBonus_lo;/* 0x0C10 */
	uint32_t 							cre_pm_HPBonus_hi;/* 0x0C14 */
	uint8_t								cre_pm_HasPrePolyCP;/* 0x0C18 */
	uint8_t								spacer5_138;/* 0x0C19 */
	uint8_t								spacer5_139;/* 0x0C1A */
	uint8_t								spacer5_140;/* 0x0C1B */
	uint32_t							cre_is_polymorphing;	/* 0C20 */
	uint32_t							cre_poly_locked;	/* 0C24 */
	CNWSCreatureAppearanceInfo			cre_appearance_info;
	CNWSCreatureStats					*cre_stats;			/* 0x0C64 */
	uint32_t							field_C68;
	uint32_t							field_C6C;

	CNWSCreature_s(int a2, unsigned int a3, unsigned int a4);
	~CNWSCreature_s();
	
	int					AddAttackActions(unsigned long feat, int a1, int a2, int a3);
	void				RemoveToAssociateList(nwn_objid_t oID);
	int					ReprocessAssociateList();
	void				UpdatePersonalSpace();
	void				AddToAssociateList(nwn_objid_t oID);
	void				AddAssociate(nwn_objid_t oID, unsigned short nType);
	void				ActivityManager(unsigned long Activity);
	unsigned char		CanEquipItem(CNWSItem *item, unsigned long *a1, int a2, int a3, int a4, CNWSPlayer *player);
	signed int 			AcquireItem(CNWSItem **Item, uint32_t From_oID, uint32_t a4, char a5, char a6, int a7, int bUpdateEncumbrance);
	int					EquipItem(unsigned long slot, CNWSItem *item, int a1, int a2);
	int					UnequipItem(CNWSItem *item, int a1);	
	int					ApplyDiseasePayload(CGameEffect *eff, unsigned long a3, unsigned long a4);
	int 				ApplyPoisonPayload(CGameEffect *eff, unsigned long t1, unsigned long t2);
	void 				CancelRest(unsigned short a1);
	int 				GetBlind();
	int					GetDamageFlags();
	CNWSFaction *		GetFaction();
	bool 				GetFlanked(CNWSCreature *Target);
	int 				GetFlatFooted();
	int 				GetInvisible(CNWSObject* obj, int i);
	int16_t 			GetMaxHitPoints(int a2);
	nwn_objid_t			GetNearestEnemy(float fDistance, unsigned long a2, int a3, int a4);
	int 				GetRangeWeaponEquipped();
	int 				GetRelativeWeaponSize(CNWSItem *weapon);
	int 				GetWeaponPower(CNWSItem *weapon, int n);
	//1 - attack bonus, 2 - damage bonus
	int 				GetTotalEffectBonus(char a2, CNWSObject *obj_a, int a4, int a5, unsigned __int8 a6, unsigned __int8 a7, unsigned __int8 a8, unsigned __int8 a9, int a10);
	CNWVisibilityNode *	GetVisibleListElement(unsigned long ul);
	float 				MaxAttackRange(nwn_objid_t, int, int);
	void 				PostProcess();
	void 				ReceiveAssociateCommand(int a1);
	void 				RemoveBadEffects();
	void				RemoveFromArea(int AreaID);
	signed int 			RemoveItem(CNWSItem *a2, int a3, int bSendFeedBack, int a5, int a6);
	int					RemoveItemFromRepository(CNWSItem *item, int a1);
	void				ResolveAttack(int a2_target_oid, signed int a3, int a4);
	int					ResolveRangedAttack(CNWSObject *Defender_a2, int nAttacks_a3, int a4);
	void				ResolveInitiative();
	void				*Rest(int a2, int bCreatureToEnemyLineOfSightCheck);
	void				RestoreItemProperties();
	void				SendFeedbackMessage(unsigned short, CNWCCMessageData *, CNWSPlayer *);
	void				SetAnimation(int nAnim);
	void				*SetScriptName(signed int iScript, CExoString ScriptName);
	void				StartGuiTimingBar(unsigned long, unsigned char);
	void				StopGuiTimingBar();
	void				SummonAssociate(CResRef resref, char*name, unsigned long len, unsigned short type);
	void				UpdateAutoMap(uint32_t areaid);
	void				PossessCreature(nwn_objid_t oID);
	void				PossessFamiliar();
	int					GetUseMonkAbilities();
	void				UpdateEncumbranceState(int bFeedback);
	void				SetPVPPlayerLikesMe(unsigned long oid_Player2, int a3, int a4);
	void				SetActivity(int Activity, int bOn);
	void				SetCombatMode(int Mode, int bOn);
	int					ToggleMode(unsigned char Mode);
	void				NotifyAssociateActionToggle(int Action);
	int					GetArmorClass();
	void				UnpossessCreature();
	void				UnpossessFamiliar();
	int					HasFeat( unsigned short nFeat);
	void				UpdateAppearanceDependantInfo();
	void				UpdateAppearanceForEquippedItems();
	void				UpdateEffectPointers();
	bool				GetMode( unsigned char mode);
	CNWSCreatureStats *	GetStats();
	void				BroadcastAttackOfOpportunity(unsigned long l, int nUnknown);
	CNWSQuickbarButton * GetQuickbarButton(unsigned char nTh);
	int					Polymorph(int nPoly, CGameEffect *eff, int nLock);
	int					UnPolymorph(CGameEffect *eff);
	int					GetIsPossessedFamiliar();
	int					GetIsInUseRange(int n1, float f, int n2);
	int					CanUseItem(CNWSItem *item, int a1);
	CExoString			GetFamiliarName();
	CExoString			GetAnimalCompanionName();
	unsigned long		GetAssociateId(unsigned short type, int nTh);
	void				SetEffectSpellId(unsigned long ID);
	float				GetMovementRateFactor();
	int					SetMovementRateFactor(float fSpeed);
	//void				Destructor(char c);
	void				ResolveMeleeAttack(CNWSObject *target, int num_attacks, int time_animation);
	void				ResolveAttackRoll(CNWSObject *obj);
	void				ResolveDamage(CNWSObject *obj);
	void				ResolvePostMeleeDamage(CNWSObject *obj);
	void				ResolveMeleeAnimations(int a1, int a2, CNWSObject *obj, int a4);
	void				ResolvePostRangedDamage(CNWSObject *obj);
	void				ResolveRangedAnimations(CNWSObject *obj, int a1);
	
	void SetAutoMapData(int a2, int a3, int a4);
};
#endif /* _NX_NWN_STRUCT_CNWSCREATURE_ */
/* vim: set sw=4: */