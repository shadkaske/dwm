/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";
static const char col_gray1[]       = "#2E3440";
static const char col_gray2[]       = "#4C566A";
static const char col_gray3[]       = "#D8DEE9";
static const char col_gray4[]       = "#3B4252";
static const char col_cyan[]        = "#88C0D0";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"setxkbmap", "-option", "ctrl:nocaps", NULL,
    "nm-applet", NULL,
    "greenclip", "daemon", NULL,
    "unclutter", "-idle", "5", NULL,
    "volumeicon", NULL,
    "sxhkd", NULL,
    "lxpolkit", NULL,
    "lxsession", NULL,
    "dunst", "-config", "~/.config/dunst/dunstrc", NULL,
    "udiskie", NULL,
    "picom", NULL,
    "mate-power-manager", NULL,
    "wmname", "LG3D", NULL,
    "slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                                  instance                            title       tags mask     isfloating   isterminal  noswallow monitor    scratch key */
	{ "Gimp",                                 NULL,                               NULL,       0,            1,           0,          0,        -1,        0  },
	{ "Arandr",                               NULL,                               NULL,       0,            1,           0,          0,        -1,        0  },
	{ NULL,                                   NULL,          "Virtual Machine Manager",       0,            1,           0,          0,        -1,        0  },
	{ "VirtualBox Manager",                   NULL,                               NULL,       0,            1,           0,          0,        -1,        0  },
	{ NULL,                                   NULL,    "Remmina Remote Desktop Client",       0,            1,           0,          0,        -1,        0  },
	{ NULL,                         "virt-manager",            "Windows10 on QEMU/KVM",       1 << 7,       0,           0,          0,        -1,        0  },
	{ "VirtualBox Machine",                   NULL,                               NULL,       1 << 7,       0,           0,          0,        -1,        0  },
	{ "qutebrowser",                          NULL,                               NULL,       1 << 2,       0,           0,          0,        -1,        0  },
	{ "DBeaver",                              NULL,                               NULL,       1 << 6,       0,           0,          0,         1,        0  },
	{ "firefox",                              NULL,                               NULL,       1 << 1,       0,           0,         -1,        -1,        0  },
	{ "Emacs",                                NULL,                               NULL,       1 << 3,       0,           0,          0,        -1,        0  },
	{ NULL,                   "outlook.office.com",                               NULL,       1 << 3,       0,           0,          0,        -1,        0  },
	{ NULL, "showplacecabinetry-team.monday.com__boards_1284644165",              NULL,       1 << 1,       0,           0,          0,        -1,        0  },
	{ "teams-for-linux",                      NULL,                               NULL,       1 << 3,       0,           0,          0,         1,        0  },
	{ "St",                                   NULL,                               NULL,       0,            0,           1,          0,        -1,        0  },
	{ "Alacritty",                            NULL,                               NULL,       0,            0,           1,          0,        -1,        0  },
	{ NULL,                                   NULL,                       "scratchpad",       0,            1,           0,          0,        -1,       's' },
	{ NULL,                                   NULL,                     "musicmanager",       0,            1,           0,          0,        -1,       'm' },
	{ NULL,                                   NULL,                        "quickedit",       0,            1,           0,          0,        -1,       'e' },
	{ NULL,                                   NULL,                      "filemanager",       0,            1,           0,          0,        -1,       'f' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
static const char *termcmd[]  = { "alacritty", NULL };
static const char *scratchpadcmd[] = {"s", "alacritty", "-t", "scratchpad", "-e", "scratchpad", NULL};
static const char *musicmanager[]  = {"m", "alacritty", "-t", "musicmanager", "-e", "ncmpcpp"};
static const char *filemanager[]  =  {"f", "alacritty", "-t", "filemanager", "-e", "ranger"};
static const char *quickedit[]     = {"e", "alacritty", "-t", "quickedit", "-e", "nvim"};

#include "focusurgent.c"
#include "movestack.c"
/*First arg only serves to match against key in rules*/

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_m,      togglescratch,  {.v = musicmanager } },
	{ MODKEY|ShiftMask,             XK_f,      togglescratch,  {.v = filemanager } },
	{ MODKEY|ShiftMask,             XK_e,      togglescratch,  {.v = quickedit } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_apostrophe,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
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
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
	{ MODKEY,                       XK_u,      focusurgent,    {0} },
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

