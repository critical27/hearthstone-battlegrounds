#pragma once

// -----------------------------------------------------------------------------
// Tribes
// -----------------------------------------------------------------------------

enum class Tribe {
    None,
    Murloc,
    Demon,
    Mech,
    Beast,
    Dragon,
    All,
};

const int TRIBE_COUNT = 7;

// -----------------------------------------------------------------------------
// Minion types
// -----------------------------------------------------------------------------

enum class MinionType : unsigned char {
    None,
    // Tier 1
    Alleycat,
    DireWolfAlpha,
    Mecharoo,
    MicroMachine,
    MurlocTidecaller,
    MurlocTidehunter,
    RighteousProtector,
    RockpoolHunter,
    SelflessHero,
    Voidwalker,
    VulgarHomunculus,
    WrathWeaver,
    // Tier 2
    AnnoyOTron,
    HarvestGolem,
    KaboomBot,
    KindlyGrandmother,
    MetaltoothLeaper,
    MountedRaptor,
    MurlocWarleader,
    NathrezimOverseer,
    OldMurkEye,
    PogoHopper,
    RatPack,
    ScavengingHyena,
    ShieldedMinibot,
    SpawnOfNZoth,
    Zoobot,
    // Tier 3
    CobaltGuardian,
    ColdlightSeer,
    CrowdFavorite,
    Crystalweaver,
    FloatingWatcher,
    Houndmaster,
    ImpGangBoss,
    InfestedWolf,
    Khadgar,
    PackLeader,
    PhalanxCommander,
    PilotedShredder,
    PsychOTron,
    ReplicatingMenace,
    ScrewjankClunker,
    ShifterZerus,
    SoulJuggler,
    TheBeast,
    TortollanShellraiser,
    // Tier 4
    AnnoyOModule,
    BolvarFireblood,
    CaveHydra,
    DefenderOfArgus,
    FesterootHulk,
    IronSensei,
    MechanoEgg,
    MenagerieMagician,
    PilotedSkyGolem,
    SecurityRover,
    Siegebreaker,
    TheBoogeymonster,
    Toxfin,
    VirmenSensei,
    // Tier 5
    AnnihilanBattlemaster,
    BaronRivendare,
    BrannBronzebeard,
    GoldrinnTheGreatWolf,
    IronhideDirehorn,
    Junkbot,
    KingBagurgle,
    LightfangEnforcer,
    MalGanis,
    PrimalfinLookout,
    SatedThreshadon,
    SavannahHighmane,
    StrongshellScavenger,
    Voidlord,
    // Tier 6
    FoeReaper4000,
    GentleMegasaur,
    Ghastcoiler,
    KangorsApprentice,
    Maexxna,
    MamaBear,
    SneedsOldShredder,
    ZappSlywick,
    // Tokens
    Amalgam,
    BigBadWolf,
    DamagedGolem,
    EmperorCobra,
    FinkleEinhorn,
    GuardBot,
    HenchClanSquire,
    Hyena,
    Imp,
    IronhideRunt,
    JoEBot,
    Microbot,
    MurlocScout,
    Plant,
    Primalfin,
    Rat,
    Robosaur,
    Safeguard,
    Snake,
    Spider,
    Tabbycat,
    VaultSafe,
    // Tokens
    NightmareAmalgam,
};

const int MINIONTYPE_COUNT = 107;

// -----------------------------------------------------------------------------
// Heroes and hero powers
// -----------------------------------------------------------------------------

enum class HeroType {
    None,
    AFKay,
    ArchVillainRafaam,
    Bartendotron,
    BrannBronzebeard,
    DancinDeryl,
    EdwinVanCleef,
    EliseStarseeker,
    GeorgeTheFallen,
    Giantfin,
    InfiniteToki,
    KelThuzad,
    KingMukla,
    LichBazhial,
    LordJaraxxus,
    MillificentManastorm,
    Nefarian,
    PatchesThePirate,
    Patchwerk,
    ProfessorPutricide,
    Pyramad,
    QueenWagtoggle,
    RagnarosTheFirelord,
    Shudderwock,
    Sindragosa,
    SirFinleyMrrgglton,
    SylvanasWindrunner,
    TheCurator,
    TheGreatAkazamzarak,
    TheLichKing,
    TheRatKing,
    TradePrinceGallywix,
    YoggSaronHopesEnd,
};

const int HEROTYPE_COUNT = 33;
