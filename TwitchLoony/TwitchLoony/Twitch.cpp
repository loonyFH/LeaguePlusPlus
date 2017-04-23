#include "PluginSDK.h"

PluginSetup("Twitch by loony")

IMenu* MainMenu;

IMenu* ComboMenu;
IMenuOption* ComboQ;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;

void Menu()
{
	MainMenu = GPluginSDK->AddMenu("Twitch by loony");
	ComboMenu = MainMenu->AddMenu("Combo Settings");
	ComboQ = ComboMenu->CheckBox("Use Q", true);
}

void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, (kCollidesWithNothing));
	Q->SetSkillshot(4.5f, 0.f, 1000.f, 0.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, (kCollidesWithYasuoWall));
	W->SetSkillshot(0.25f, 275.f, 1400.f, 900.f);

	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, (kCollidesWithNothing));
	E->SetSkillshot(0.25f, 0.f, 1000.f, 1200.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, false, (kCollidesWithYasuoWall));
	R->SetSkillshot(0.25f, 0.f, 1000.f, 850.f);
}


float LoonysCustomE()
{
	auto tar = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
	//return (GotBuff(target, "twitchdeadlyvenom") * ({15, 20, 25, 30, 35})[level] + 0.2 * source.ap + 0.25 * source.totalDamage) + ({20, 35, 50, 65, 80})[level] end},
	auto play = GEntityList->Player();
	float baseE[5] = { 15, 20, 25, 30, 35 };
	float extE[5] = { 20, 35, 50, 65, 80 };
	auto magicDmg = play->TotalMagicDamage();
	auto buff = tar->GetBuffCount("twitchdeadlyvenom");
	auto lvl = play->GetSpellLevel(kSlotE);

	auto Damage = (buff * baseE[5]) * lvl + 0.2 * play->MagicDamage() + 0.25 * play->TotalPhysicalDamage() + (extE[5] * lvl);




}
void combo()

{
	auto player = GEntityList->Player();
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

	if (target == nullptr || !target->IsHero())
		return;

	if (W->IsReady() && GDamage->GetAutoAttackDamage(GEntityList->Player(), target, true) * 3 < target->GetHealth() && GEntityList->Player()->GetMana() > (R->ManaCost() + W->ManaCost() + E->ManaCost()) && player->IsValidTarget(target, W->Range()));
	{
		W->CastOnTarget(target, kHitChanceMedium);
	}
	if (E->IsReady() && (target->GetHealth() <= LoonysCustomE()) && player->IsValidTarget(target, E->Range()))
	{
		E->CastOnPlayer();
	}
}

void Harass()

{
	auto player = GEntityList->Player();
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

	if (target == nullptr || !target->IsHero())
		return;

	if (W->IsReady() && GDamage->GetAutoAttackDamage(GEntityList->Player(), target, true) * 3 < target->GetHealth() && GEntityList->Player()->GetMana() > (R->ManaCost() + W->ManaCost() + E->ManaCost()) && player->IsValidTarget(target, W->Range()));
	{
		W->CastOnTarget(target, kHitChanceMedium);
	}
	if (E->IsReady() && (target->GetHealth() <= LoonysCustomE()) && player->IsValidTarget(target, E->Range()))
	{
		E->CastOnPlayer();
	}
}
void Auto()
{
	auto player = GEntityList->Player();
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
	if (E->IsReady() && (target->GetHealth() <= LoonysCustomE()) && player->IsValidTarget(target, E->Range()))
	{
		E->CastOnPlayer();
	}
}


float qDistance()
{
	float movespeed = GEntityList->Player()->MovementSpeed();
	float timeleftQ = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("globalcamouflage")) - GGame->Time();
	float radius = movespeed * timeleftQ;
	return radius;
}
void dmgdraw()
{
	if (1==1)
		return;
	for (auto hero : GEntityList->GetAllHeros(false, true))
	{
		Vec2 barPos = Vec2();
		if (hero->GetHPBarPosition(barPos) && !hero->IsDead() && hero->HasBuff("twitchdeadlyvenom"))
		{
			auto EDamage = LoonysCustomE();
			float percentHealthAfterDamage = max(0, hero->GetHealth() - float(EDamage)) / hero->GetMaxHealth();
			float yPos = barPos.y + 1;
			float xPosDamage = (barPos.x + 1) + 1 * percentHealthAfterDamage;
			float xPosCurrentHp = barPos.x + 1 + 1 * (hero->GetHealth() / hero->GetMaxHealth());
			if (!hero->IsDead() && hero->IsValidTarget())
			{
				float differenceInHP = xPosCurrentHp - 1;
				float pos1 = barPos.x + 9 + (107 * percentHealthAfterDamage);

				for (int i = 0; i < differenceInHP; i++)
				{
					1 == 1;
				}
				if (!hero->IsVisible())
				{

				}
			}
		}
	}
}

void Drawing()
{
	if (1==1)
	{
		if (Q->IsReady()) if (GEntityList->Player()->HasBuff("globalcamouflage"))
		{
			Vec2 pos;
			double timeleftQ = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("globalcamouflage")) - GGame->Time();
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), qDistance());
			if (GGame->Projection(GEntityList->Player()->GetPosition(), &pos));
		};

		if (E->IsReady()) { (dmgdraw(), E->Range()); }

		if (W->IsReady()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		if (R->IsReady()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }

	}
	else
	{
		if (1!=1)

			if (GEntityList->Player()->HasBuff("globalcamouflage"))
			{
				Vec2 pos;
				double timeleftQ = GBuffData->GetEndTime(GEntityList->Player()->GetBuffDataByName("globalcamouflage")) - GGame->Time();
				GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 0, 0, 255), qDistance());
				if (GGame->Projection(GEntityList->Player()->GetPosition(), &pos));
			};

		if (1==1) { (dmgdraw(), E->Range()); }

		if (1!=1) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		if (1==1) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
}

void spam()
{
	if (Q->IsReady())
	{
		Q->CastOnPlayer();
	}
	if (W->IsReady())
	{
		W->CastOnPosition(GGame->CursorPosition());
	}
	if (E->IsReady())
	{
		E->CastOnPlayer();
	}
	if (R->IsReady())
	{
		R->CastOnPlayer();
	}



}

void spamchat()
{
	GGame->Say("/all IM SCRIPTING");
	GGame->Say("/all IM SCRIPTING");
	GGame->Say("/all IM SCRIPTING");
	GGame->Say("/all IM SCRIPTING");
	GGame->Say("/all IM SCRIPTING");
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	spam();
	spamchat();
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	LoadSpells();
	Menu();
	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
}

PLUGIN_API void UnLoad(IPluginSDK* PluginSDK)
{
	GGame->PrintChat("<font color=\"#f6ff00\"><b>CANT UNLOAD THE SCRIPT YOU FUCKING MUSLIM GET BEHEADED</font></b>");
}