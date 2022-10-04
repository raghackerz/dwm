/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { 
  "Linux Libertine:weight=medium:size=11:style=Bold:antialias=true:hinting=true",
  "Iosevka:weight=medium:size=20:style=Bold:antialias=true:hinting=true"
};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#1a1b26";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_bordercolor[] = "#b30000";
static const char col1[]            = "#7aa2f7";   //kernel script(0c) blue
static const char col2[]            = "#e0af68";   //cpu prcentage(0d) yellow
static const char col3[]            = "#7dcfff";   //cputemp(0e)       
static const char col4[]            = "#bb9af7";   //disku(0f)         purple
static const char col5[]            = "#f7768e";   //memory(10)        red
static const char col6[]            = "#646464";   //disabled(11)      grey
static const char col7[]            = "#81a1c1";   //charger(12)      
static const char col8[]            = "#0bfab0";   //volume(13)        greenblue
static const char col9[]            = "#46d9ff";   //calendar(14)      lightblue
static const char col10[]           = "#9ece6a";   //battery(15)       green
// static const unsigned int baralpha = 0xd0;
static const unsigned int baralpha = OPAQUE;
static const unsigned int borderalpha = OPAQUE;

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeCol7, SchemeCol8, SchemeCol9,SchemeCol10,SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*                fg         bg         border   */
	[SchemeNorm]  = { col_gray3, col_gray1, col_gray2 },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeCol7]  = { col7,      col_gray1, col_gray2 },
	[SchemeCol8]  = { col8,      col_gray1, col_gray2 },
	[SchemeCol9]  = { col9,      col_gray1, col_gray2 },
	[SchemeCol10] = { col10,     col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col_cyan,  col_bordercolor  },
};
static const unsigned int alphas[][3]      = {
	/*                fg      bg        border     */
	[SchemeNorm]  = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]   = { OPAQUE, baralpha, borderalpha },
	[SchemeCol1]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol2]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol3]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol4]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol5]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol6]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol7]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol8]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol9]  = { OPAQUE, baralpha, borderalpha},
	[SchemeCol10] = { OPAQUE, baralpha, borderalpha},
};

/* tagging */
static const char *tags[] = {"","","","","","","","",""};
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)												\
	{1, {{MODKEY, KEY}},								        view,           {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},					  toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},						  tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},  toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *volinc[] = {"sigdwmblocks", "8", "1"};
static const char *voldec[]= {"sigdwmblocks", "8", "2"};
static const char *volmute[]= {"sigdwmblocks", "8", "3"};
static const char *browser[] = {"brave"};
static const char *incognito_browser[] = {"brave","--incognito"};

static Keychord keychords[] = {
	/* modifier                         key          function        argument */
	{1, {{MODKEY|ShiftMask,             XK_Return}}, spawn,          {.v = dmenucmd } },
	{1, {{MODKEY,                       XK_Return}}, spawn,          {.v = termcmd } },
	{1, {{MODKEY,                       XK_b}},      spawn,          {.v = browser } },
	{1, {{MODKEY|ShiftMask,             XK_b}},      spawn,          {.v = incognito_browser } },
	{1, {{MODKEY,                       XK_s}},      togglebar,      {0} },
	{1, {{MODKEY,                       XK_j}},      focusstack,     {.i = +1 } },
	{1, {{MODKEY,                       XK_k}},      focusstack,     {.i = -1 } },
	{1, {{MODKEY,                       XK_i}},      incnmaster,     {.i = +1 } },
	{1, {{MODKEY,                       XK_d}},      incnmaster,     {.i = -1 } },
	{1, {{MODKEY,                       XK_h}},      setmfact,       {.f = -0.05} },
	{1, {{MODKEY,                       XK_l}},      setmfact,       {.f = +0.05} },
	{1, {{MODKEY,                       XK_p}},      zoom,           {0} },
	{1, {{MODKEY,                       XK_Tab}},    view,           {0} },
	{1, {{MODKEY|ShiftMask,             XK_c}},      killclient,     {0} },
	{1, {{MODKEY,                       XK_t}},      setlayout,      {.v = &layouts[0]} },
	//{1, {{MODKEY,                       XK_f}},      setlayout,      {.v = &layouts[1]} },
	{1, {{MODKEY,                       XK_m}},      setlayout,      {.v = &layouts[2]} },
	{1, {{MODKEY,                       XK_space}},  setlayout,      {0} },
	{1, {{MODKEY|ShiftMask,             XK_space}},  togglefloating, {0} },
	{1, {{MODKEY,                       XK_f}},      togglefullscr,  {0} },
	{1, {{MODKEY,                       XK_0}},      view,           {.ui = ~0 } },
	{1, {{MODKEY|ShiftMask,             XK_0}},      tag,            {.ui = ~0 } },
	{1, {{MODKEY,                       XK_comma}},  focusmon,       {.i = -1 } },
	{1, {{MODKEY,                       XK_period}}, focusmon,       {.i = +1 } },
	{1, {{MODKEY|ShiftMask,             XK_comma}},  tagmon,         {.i = -1 } },
	{1, {{MODKEY|ShiftMask,             XK_period}}, tagmon,         {.i = +1 } },
	{1, {{MODKEY,                       XK_minus}},  setgaps,        {.i = -1 } },
	{1, {{MODKEY,                       XK_equal}},  setgaps,        {.i = +1 } },
	{1, {{MODKEY|ShiftMask,             XK_equal}},  setgaps,        {.i = 0  } },
  {1, {{0,                            0x1008ff13}},spawn,          {.v = volinc} },
  {1, {{0,                            0x1008ff11}},spawn,          {.v = voldec} },
  {1, {{0,                            0x1008ff12}},spawn,          {.v = volmute} },
  
  {1, {{MODKEY|ShiftMask,             XK_x}},     spawn,          SHCMD("/home/raghackerz/.scripts/shutdown") },
  {1, {{MODKEY,                       XK_F8}},    spawn,          SHCMD("/home/raghackerz/.scripts/keyboard") },
  {1, {{0,                            XK_Print}}, spawn,          SHCMD("/home/raghackerz/.scripts/screenshots") },

  {3, {{MODKEY,XK_semicolon},{0,XK_w},{0,XK_s}},  spawn,          SHCMD("/home/raghackerz/.scripts/wallpaperselector") },
  {3, {{MODKEY,XK_semicolon},{0,XK_w},{0,XK_r}},  spawn,          SHCMD("/home/raghackerz/.scripts/randomwallpaper") },
  {2, {{MODKEY,XK_semicolon},{0,XK_i}},           spawn,          SHCMD("/home/raghackerz/.scripts/important") },
	TAGKEYS(                            XK_1,                        0)
	TAGKEYS(                            XK_2,                        1)
	TAGKEYS(                            XK_3,                        2)
	TAGKEYS(                            XK_4,                        3)
	TAGKEYS(                            XK_5,                        4)
	TAGKEYS(                            XK_6,                        5)
	TAGKEYS(                            XK_7,                        6)
	TAGKEYS(                            XK_8,                        7)
	TAGKEYS(                            XK_9,                        8)
	{1, {{MODKEY|ShiftMask,             XK_q}},      quit,           {0} },
	{1, {{MODKEY|ControlMask|ShiftMask, XK_q}},      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

