/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
// for pulse compatible //
static const char *upvol[] = { "amixer", "-q", "sset", "Master", "5%+", NULL  };
static const char *downvol[] = { "amixer", "-q", "sset", "Master", "5%-", NULL  };
static const char *mute[] = { "amixer", "-q", "-D", "pulse", "sset", "Master", "toggle", NULL  };
static const char *pkillvol[] = { "pkill", "-RTMIN+10", "dwmblocks", NULL  };
static const char *uplight[] = { "xbacklight", "-inc", "1", NULL  };
static const char *downlight[] = { "xbacklight", "-dec", "1", NULL  };
static const char *pkilllight[] = { "pkill", "-RTMIN+11", "dwmblocks", NULL  };
static const char *touchpad[] = { "/usr/local/bin/toggletouchpad.sh", NULL  };
static const char *print[] = { "gnome-screenshot", "-i", NULL  };
static const char *suspend[] = { "sudo", "s2ram", NULL  };
static const char *saver[] = { "xset", "dpms", "force", "off", NULL  };
static const char *play[] = { "cmus-remote", "--pause", NULL  };
static const char *stop[] = { "cmus-remote", "--perv", NULL,  };
static const char *next[] = { "cmus-remote", "--next", NULL,  };
static const char *prev[] = { "cmus-remote", "--seek", "-5", NULL  };
static const char *playctl[] = { "playerctl", "--player=spotify", "play-pause", NULL  };
static const char *stopctl[] = { "playerctl", "--player=spotify", "stop", NULL  };
static const char *nextctl[] = { "playerctl", "--player=spotify", "next", NULL  };
static const char *prevctl[] = { "playerctl", "--player=spotify", "previous", NULL  };
static const char *upkbd[] = { "/home/salar/local/bin/kb-light.py", "+", "1", NULL  };
static const char *downkbd[] = { "/home/salar/local/bin/kb-light.py", "-", "1", NULL  };
static const char *wifi[] = { "sudo", "etc/init.d/net.wlp3s0", "start", NULL  };
static const char *red3000[] = { "redshift", "-P", "-O", "3000", NULL  };
static const char *red4000[] = { "redshift", "-P", "-O", "4000", NULL  };
static const char *red6000[] = { "redshift", "-P", "-O", "6000", NULL  };
static const char *tlp[] = { "sudo", "tlp", "start", NULL  };



static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ 0,		XF86XK_WLAN,			spawn,		{.v = wifi } },
	{ 0,		XF86XK_TouchpadToggle,		spawn,		{.v = touchpad } },
	{ 0,		XF86XK_AudioPlay,		spawn,		{.v = play } },
	{ 0,		XF86XK_AudioPlay,		spawn,		{.v = playctl } },
	{ 0,		XF86XK_AudioStop,		spawn,		{.v = stop } },
	{ 0,		XF86XK_AudioStop,		spawn,		{.v = stopctl } },
	{ 0,		XF86XK_AudioNext,		spawn,		{.v = next } },
	{ 0,		XF86XK_AudioNext,		spawn,		{.v = nextctl } },
	{ 0,		XF86XK_AudioPrev,		spawn,		{.v = prev } },
	{ 0,		XF86XK_AudioPrev,		spawn,		{.v = prevctl } },
	{ 0,		XF86XK_KbdBrightnessUp,		spawn,		{.v = upkbd } },
	{ 0,		XF86XK_KbdBrightnessDown,	spawn,		{.v = downkbd } },
	{ MODKEY,			XK_z,		spawn,		{.v = red3000 } },
	{ MODKEY,			XK_x,		spawn,		{.v = red4000 } },
	{ MODKEY,			XK_c,		spawn,		{.v = red6000 } },
	{ MODKEY,			XK_v,		spawn,		{.v = tlp } },
	{ 0,		XF86XK_AudioRaiseVolume,	spawn,		{.v = upvol } },
	{ 0,		XF86XK_AudioRaiseVolume,	spawn,		{.v = pkillvol } },
	{ 0,		XF86XK_AudioLowerVolume,	spawn,		{.v = downvol } },
	{ 0,		XF86XK_AudioLowerVolume,	spawn,		{.v = pkillvol } },
	{ 0,		XF86XK_AudioMute,		spawn,		{.v = mute } },
	{ 0,		XF86XK_AudioMute,		spawn,		{.v = pkillvol } },
	{ 0,		XF86XK_MonBrightnessUp,		spawn,		{.v = uplight } },
	{ 0,		XF86XK_MonBrightnessUp,		spawn,		{.v = pkilllight } },
	{ 0,		XF86XK_MonBrightnessDown,	spawn,		{.v = downlight } },
	{ 0,		XF86XK_MonBrightnessDown,	spawn,		{.v = pkilllight } },
	{ 0,		XK_Print,			spawn,		{.v = print } },
	{ 0,		XF86XK_Sleep,			spawn,		{.v = suspend } },
	{ 0,		XF86XK_ScreenSaver,		spawn,		{.v = saver } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

