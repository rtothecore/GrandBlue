#ifndef _TEST_RESOURCE_H_
#define _TEST_RESOURCE_H_

// PList
static const char p_Dolphin[]              = "zwoptex/dolphin.plist";
static const char s_Dolphin[]              = "dolphin1.png";

static const char p_Diver[]                = "zwoptex/diver.plist";
static const char s_Diver[]                = "diver1.png";

static const char p_Bye[]                = "zwoptex/bye.plist";
static const char s_Bye[]                = "bye1.png";

static const char p_Love[]                = "zwoptex/love.plist";
static const char s_Love[]                = "love1.png";

static const char p_Turtle[]              = "zwoptex/turtle.plist";
static const char s_Turtle[]              = "turtle1.png";

static const char p_Squid[]              = "zwoptex/squid.plist";
static const char s_Squid[]              = "squid1.png";

static const char p_Starfish[]              = "zwoptex/starfish.plist";
static const char s_Starfish[]              = "starfish1.png";

static const char p_Seahorse[]				= "zwoptex/seahorse.plist";
static const char s_Seahorse[]				= "seahorse1.png";

static const char p_Mermaid[]				= "zwoptex/mermaid.plist";
static const char s_Mermaid[]				= "mermaid1.png";

static const char p_Ray[]				= "zwoptex/ray.plist";
static const char s_Ray[]				= "ray1.png";

static const char p_Jellyfish[]				= "zwoptex/jellyfish.plist";
static const char s_Jellyfish[]				= "jellyfish1.png";

static const char p_Orca[]				= "zwoptex/orca.plist";
static const char s_Orca[]				= "orca1.png";

static const char p_Brain[]				= "zwoptex/brain.plist";
static const char s_Brain[]				= "brain1.png";


// Image
static const char s_UnderSea[]			   = "underTheSea_light.png";
static const char s_Rocks[]				   = "underTheSea_rocks.png";
static const char s_Rope[]				   = "rope.png";

// Sound
#define MUSIC_FILE									"sound/grandblue.wav"
#define FEVER_FILE									"sound/grandblue_fever.wav"

#define EFFECT_BUBBLE_FILE							"sound/bubble.wav"

#define EFFECT_DOLPHIN1_FILE						"sound/dolphin1.wav"
#define EFFECT_DOLPHIN2_FILE						"sound/dolphin2.wav"
#define EFFECT_DOLPHIN3_FILE						"sound/dolphin3.wav"

#define EFFECT_TURTLE1_FILE							"sound/turtle1.wav"
#define EFFECT_TURTLE2_FILE							"sound/turtle2.wav"
#define EFFECT_TURTLE3_FILE							"sound/turtle3.wav"

#define EFFECT_SQUID1_FILE							"sound/squid1.wav"
#define EFFECT_SQUID2_FILE							"sound/squid2.wav"
#define EFFECT_SQUID3_FILE							"sound/squid3.wav"

#define EFFECT_STARFISH1_FILE						"sound/starfish1.wav"
#define EFFECT_STARFISH2_FILE						"sound/starfish2.wav"
#define EFFECT_STARFISH3_FILE						"sound/starfish3.wav"

#define EFFECT_SEAHORSE1_FILE						"sound/seahorse1.wav"
#define EFFECT_SEAHORSE2_FILE						"sound/seahorse2.wav"

#define EFFECT_MERMAID1_FILE						"sound/mermaid1.wav"
#define EFFECT_MERMAID2_FILE						"sound/mermaid2.wav"
#define EFFECT_MERMAID3_FILE						"sound/mermaid3.wav"

#define EFFECT_RAY1_FILE							"sound/ray1.wav"
#define EFFECT_RAY2_FILE							"sound/ray2.wav"
#define EFFECT_RAY3_FILE							"sound/ray3.wav"

#define EFFECT_JELLYFISH1_FILE							"sound/jellyfish1.wav"
#define EFFECT_JELLYFISH2_FILE							"sound/jellyfish2.wav"
#define EFFECT_JELLYFISH3_FILE							"sound/jellyfish3.wav"

#define EFFECT_ORCA1_FILE							"sound/orca1.wav"
#define EFFECT_ORCA2_FILE							"sound/orca2.wav"
#define EFFECT_ORCA3_FILE							"sound/orca3.wav"

#define EFFECT_BRAIN1_FILE							"sound/brain1.wav"
#define EFFECT_BRAIN2_FILE							"sound/brain2.wav"
#define EFFECT_BRAIN3_FILE							"sound/brain3.wav"

#define EFFECT_DIVER_MEET_MARINELIFE_FILE			"sound/diver1.wav"

#define EFFECT_SCORE_FILE							"sound/score.wav"

// fonts
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #define FONT_TITLE_FILE		"American Captain Patrius 02 FRE"
    #define FONT_MENU_FILE      "Avengeance Mightiest Avenger"
#else
    #define FONT_TITLE_FILE		"fonts/American Captain Patrius 02 FRE.ttf"
    #define FONT_MENU_FILE      "fonts/AVENGEANCE MIGHTIEST AVENGER.ttf"
#endif

#endif