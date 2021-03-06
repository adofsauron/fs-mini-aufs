/*
 *   Additional mixer mapping
 *
 *   Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */


struct usbmix_name_map {
	int id;
	const char *name;
	int control;
};

struct usbmix_selector_map {
	int id;
	int count;
	const char **names;
};

struct usbmix_ctl_map {
	u32 id;
	const struct usbmix_name_map *map;
	const struct usbmix_selector_map *selector_map;
	int ignore_ctl_error;
};

/*
 * USB control mappers for SB Exitigy
 */

/*
 * Topology of SB Extigy (see on the wide screen :)

USB_IN[1] --->FU[2]------------------------------+->MU[16]-->PU[17]-+->FU[18]--+->EU[27]--+->EU[21]-->FU[22]--+->FU[23] > Dig_OUT[24]
                                                 ^                  |          |          |                   |
USB_IN[3] -+->SU[5]-->FU[6]--+->MU[14] ->PU[15]->+                  |          |          |                   +->FU[25] > Dig_OUT[26]
           ^                 ^                   |                  |          |          |
Dig_IN[4] -+                 |                   |                  |          |          +->FU[28]---------------------> Spk_OUT[19]
                             |                   |                  |          |
Lin-IN[7] -+-->FU[8]---------+                   |                  |          +----------------------------------------> Hph_OUT[20]
           |                                     |                  |
Mic-IN[9] --+->FU[10]----------------------------+                  |
           ||                                                       |
           ||  +----------------------------------------------------+
           VV  V
           ++--+->SU[11]-->FU[12] --------------------------------------------------------------------------------------> USB_OUT[13]
*/

static struct usbmix_name_map extigy_map[] = {
	/* 1: IT pcm */
	{ 2, "PCM Playback" }, /* FU */
	/* 3: IT pcm */
	/* 4: IT digital in */
	{ 5, NULL }, /* DISABLED: this seems to be bogus on some firmware */
	{ 6, "Digital In" }, /* FU */
	/* 7: IT line */
	{ 8, "Line Playback" }, /* FU */
	/* 9: IT mic */
	{ 10, "Mic Playback" }, /* FU */
	{ 11, "Capture Input Source" }, /* SU */
	{ 12, "Capture" }, /* FU */
	/* 13: OT pcm capture */
	/* 14: MU (w/o controls) */
	/* 15: PU (3D enh) */
	/* 16: MU (w/o controls) */
	{ 17, NULL, 1 }, /* DISABLED: PU-switch (any effect?) */
	{ 17, "Channel Routing", 2 },	/* PU: mode select */
	{ 18, "Tone Control - Bass", USB_FEATURE_BASS }, /* FU */
	{ 18, "Tone Control - Treble", USB_FEATURE_TREBLE }, /* FU */
	{ 18, "Master Playback" }, /* FU; others */
	/* 19: OT speaker */
	/* 20: OT headphone */
	{ 21, NULL }, /* DISABLED: EU (for what?) */
	{ 22, "Digital Out Playback" }, /* FU */
	{ 23, "Digital Out1 Playback" }, /* FU */  /* FIXME: corresponds to 24 */
	/* 24: OT digital out */
	{ 25, "IEC958 Optical Playback" }, /* FU */
	{ 26, "IEC958 Optical Playback" }, /* OT */
	{ 27, NULL }, /* DISABLED: EU (for what?) */
	/* 28: FU speaker (mute) */
	{ 29, NULL }, /* Digital Input Playback Source? */
	{ 0 } /* terminator */
};

/* Sound Blaster MP3+ controls mapping
 * The default mixer channels have totally misleading names,
 * e.g. no Master and fake PCM volume
 *			Pavel Mihaylov <bin@bash.info>
 */
static struct usbmix_name_map mp3plus_map[] = {
	/* 1: IT pcm */
	/* 2: IT mic */
	/* 3: IT line */
	/* 4: IT digital in */
	/* 5: OT digital out */
	/* 6: OT speaker */
	/* 7: OT pcm capture */
	{ 8, "Capture Input Source" }, /* FU, default PCM Capture Source */
		/* (Mic, Input 1 = Line input, Input 2 = Optical input) */
	{ 9, "Master Playback" }, /* FU, default Speaker 1 */
	/* { 10, "Mic Capture", 1 }, */ /* FU, Mic Capture */
	/* { 10, "Mic Capture", 2 }, */ /* FU, Mic Capture */
	{ 10, "Mic Boost", 7 }, /* FU, default Auto Gain Input */
	{ 11, "Line Capture" }, /* FU, default PCM Capture */
	{ 12, "Digital In Playback" }, /* FU, default PCM 1 */
	/* { 13, "Mic Playback" }, */ /* FU, default Mic Playback */
	{ 14, "Line Playback" }, /* FU, default Speaker */
	/* 15: MU */
	{ 0 } /* terminator */
};

/* Topology of SB Audigy 2 NX

          +----------------------------->EU[27]--+
          |                                      v
          | +----------------------------------->SU[29]---->FU[22]-->Dig_OUT[24]
          | |                                    ^
USB_IN[1]-+------------+              +->EU[17]->+->FU[11]-+
            |          v              |          v         |
Dig_IN[4]---+->FU[6]-->MU[16]->FU[18]-+->EU[21]->SU[31]----->FU[30]->Hph_OUT[20]
            |          ^              |                    |
Lin_IN[7]-+--->FU[8]---+              +->EU[23]->FU[28]------------->Spk_OUT[19]
          | |                                              v
          +--->FU[12]------------------------------------->SU[14]--->USB_OUT[15]
            |                                              ^
            +->FU[13]--------------------------------------+
*/
static struct usbmix_name_map audigy2nx_map[] = {
	/* 1: IT pcm playback */
	/* 4: IT digital in */
	{ 6, "Digital In Playback" }, /* FU */
	/* 7: IT line in */
	{ 8, "Line Playback" }, /* FU */
	{ 11, "What-U-Hear Capture" }, /* FU */
	{ 12, "Line Capture" }, /* FU */
	{ 13, "Digital In Capture" }, /* FU */
	{ 14, "Capture Source" }, /* SU */
	/* 15: OT pcm capture */
	/* 16: MU w/o controls */
	{ 17, NULL }, /* DISABLED: EU (for what?) */
	{ 18, "Master Playback" }, /* FU */
	/* 19: OT speaker */
	/* 20: OT headphone */
	{ 21, NULL }, /* DISABLED: EU (for what?) */
	{ 22, "Digital Out Playback" }, /* FU */
	{ 23, NULL }, /* DISABLED: EU (for what?) */
	/* 24: OT digital out */
	{ 27, NULL }, /* DISABLED: EU (for what?) */
	{ 28, "Speaker Playback" }, /* FU */
	{ 29, "Digital Out Source" }, /* SU */
	{ 30, "Headphone Playback" }, /* FU */
	{ 31, "Headphone Source" }, /* SU */
	{ 0 } /* terminator */
};

static struct usbmix_selector_map audigy2nx_selectors[] = {
	{
		.id = 14, /* Capture Source */
		.count = 3,
		.names = (const char*[]) {"Line", "Digital In", "What-U-Hear"}
	},
	{
		.id = 29, /* Digital Out Source */
		.count = 3,
		.names = (const char*[]) {"Front", "PCM", "Digital In"}
	},
	{
		.id = 31, /* Headphone Source */
		.count = 2,
		.names = (const char*[]) {"Front", "Side"}
	},
	{ 0 } /* terminator */
};

/* LineX FM Transmitter entry - needed to bypass controls bug */
static struct usbmix_name_map linex_map[] = {
	/* 1: IT pcm */
	/* 2: OT Speaker */ 
	{ 3, "Master" }, /* FU: master volume - left / right / mute */
	{ 0 } /* terminator */
};

/* Section "justlink_map" below added by James Courtier-Dutton <James@superbug.demon.co.uk>
 * sourced from Maplin Electronics (http://www.maplin.co.uk), part number A56AK
 * Part has 2 connectors that act as a single output. (TOSLINK Optical for digital out, and 3.5mm Jack for Analogue out.)
 * The USB Mixer publishes a Microphone and extra Volume controls for it, but none exist on the device,
 * so this map removes all unwanted sliders from alsamixer
 */

static struct usbmix_name_map justlink_map[] = {
	/* 1: IT pcm playback */
	/* 2: Not present */
	{ 3, NULL}, /* IT mic (No mic input on device) */
	/* 4: Not present */
	/* 5: OT speacker */
	/* 6: OT pcm capture */
	{ 7, "Master Playback" }, /* Mute/volume for speaker */
	{ 8, NULL }, /* Capture Switch (No capture inputs on device) */
	{ 9, NULL }, /* Capture Mute/volume (No capture inputs on device */
	/* 0xa: Not present */
	/* 0xb: MU (w/o controls) */
	{ 0xc, NULL }, /* Mic feedback Mute/volume (No capture inputs on device) */
	{ 0 } /* terminator */
};

/*
 * Control map entries
 */

static struct usbmix_ctl_map usbmix_ctl_maps[] = {
	{
		.id = USB_ID(0x041e, 0x3000),
		.map = extigy_map,
		.ignore_ctl_error = 1,
	},
	{
		.id = USB_ID(0x041e, 0x3010),
		.map = mp3plus_map,
	},
	{
		.id = USB_ID(0x041e, 0x3020),
		.map = audigy2nx_map,
		.selector_map = audigy2nx_selectors,
	},
	{
		/* Hercules DJ Console (Windows Edition) */
		.id = USB_ID(0x06f8, 0xb000),
		.ignore_ctl_error = 1,
	},
	{
		/* Hercules DJ Console (Macintosh Edition) */
		.id = USB_ID(0x06f8, 0xd002),
		.ignore_ctl_error = 1,
	},
	{
		.id = USB_ID(0x08bb, 0x2702),
		.map = linex_map,
		.ignore_ctl_error = 1,
	},
	{
		.id = USB_ID(0x0c45, 0x1158),
		.map = justlink_map,
	},
	{ 0 } /* terminator */
};

