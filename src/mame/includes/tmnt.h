// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
#ifndef MAME_INCLUDES_TMNT_H
#define MAME_INCLUDES_TMNT_H

#pragma once

#include "sound/samples.h"
#include "sound/upd7759.h"
#include "sound/k007232.h"
#include "sound/k053260.h"
#include "sound/k054539.h"
#include "video/k053244_k053245.h"
#include "video/k052109.h"
#include "video/k051960.h"
#include "video/k053251.h"
#include "video/k053936.h"
#include "video/k054000.h"
#include "video/konami_helper.h"
#include "emupal.h"
#include "tilemap.h"

class tmnt_state : public driver_device
{
public:
	tmnt_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_spriteram(*this, "spriteram"),
		m_tmnt2_rom(*this, "maincpu"),
		m_sunset_104000(*this, "sunset_104000"),
		m_tmnt2_1c0800(*this, "tmnt2_1c0800"),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_k007232(*this, "k007232"),
		m_k053260(*this, "k053260"),
		m_k054539(*this, "k054539"),
		m_k052109(*this, "k052109"),
		m_k051960(*this, "k051960"),
		m_k053245(*this, "k053245"),
		m_k053251(*this, "k053251"),
		m_k053936(*this, "k053936"),
		m_k054000(*this, "k054000"),
		m_upd7759(*this, "upd"),
		m_samples(*this, "samples"),
		m_gfxdecode(*this, "gfxdecode"),
		m_palette(*this, "palette")
	{ }

	void cuebrick(machine_config &config);
	void blswhstl(machine_config &config);
	void ssriders(machine_config &config);
	void tmnt2(machine_config &config);
	void lgtnfght(machine_config &config);
	void thndrx2(machine_config &config);
	void sunsetbl(machine_config &config);
	void tmnt(machine_config &config);
	void tmntucbl(machine_config &config);
	void mia(machine_config &config);
	void punkshot(machine_config &config);

	void init_mia();
	void init_tmnt();
	void init_cuebrick();
	void init_thndrx2();

protected:
	virtual void machine_start() override;

	enum
	{
		TIMER_NMI
	};

	/* memory pointers */
	optional_shared_ptr<uint16_t> m_spriteram;
	required_region_ptr<uint16_t> m_tmnt2_rom;
	optional_shared_ptr<uint16_t> m_sunset_104000;
	optional_shared_ptr<uint16_t> m_tmnt2_1c0800;

	/* video-related */
	int        m_layer_colorbase[3]{};
	int        m_sprite_colorbase = 0;
	int        m_layerpri[3]{};
	int        m_sorted_layer[3]{};   // this might not be necessary, but tmnt2 uses it in a strange way...

	tilemap_t  *m_roz_tilemap = nullptr;
	int        m_glfgreat_pixel = 0;
	int        m_blswhstl_rombank = 0;
	int        m_tmnt_priorityflag = 0;
	int        m_lastdim = 0;
	int        m_lasten = 0;
	int        m_dim_c = 0;
	int        m_dim_v = 0; /* lgtnfght, ssriders, tmnt2 only */

	/* misc */
	int        m_tmnt_soundlatch = 0;
	int        m_toggle = 0;
	int        m_last = 0;
	uint16_t     m_cuebrick_nvram[0x400 * 0x20 / 2];  // 32k paged in a 1k window

	/* devices */
	required_device<cpu_device> m_maincpu;
	optional_device<cpu_device> m_audiocpu;
	optional_device<k007232_device> m_k007232;
	optional_device<k053260_device> m_k053260;
	optional_device<k054539_device> m_k054539;
	required_device<k052109_device> m_k052109;
	optional_device<k051960_device> m_k051960;
	optional_device<k05324x_device> m_k053245;
	optional_device<k053251_device> m_k053251;
	optional_device<k053936_device> m_k053936;
	optional_device<k054000_device> m_k054000;
	optional_device<upd7759_device> m_upd7759;
	optional_device<samples_device> m_samples;
	optional_device<gfxdecode_device> m_gfxdecode;
	required_device<palette_device> m_palette;

	/* memory buffers */
	int16_t      m_sampledata[0x40000];

	uint8_t      m_irq5_mask = 0;
	uint16_t k052109_word_noA12_r(offs_t offset);
	void k052109_word_noA12_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void punkshot_k052109_word_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void punkshot_k052109_word_noA12_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint16_t k053245_scattered_word_r(offs_t offset);
	void k053245_scattered_word_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint16_t k053244_word_noA1_r(offs_t offset);
	void k053244_word_noA1_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint8_t tmnt_sres_r();
	void tmnt_sres_w(uint8_t data);
	void sound_arm_nmi_w(uint8_t data);
	uint16_t punkshot_kludge_r();
	uint16_t ssriders_protection_r(address_space &space);
	void ssriders_protection_w(address_space &space, offs_t offset, uint16_t data);
	uint16_t blswhstl_coin_r();
	uint16_t ssriders_eeprom_r();
	uint16_t sunsetbl_eeprom_r();
	void blswhstl_eeprom_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint16_t thndrx2_eeprom_r();
	void thndrx2_eeprom_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void cuebrick_nvbank_w(uint8_t data);
	void ssriders_soundkludge_w(uint16_t data);
	void tmnt2_1c0800_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void tmnt_0a0000_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void punkshot_0a0020_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void lgtnfght_0a0018_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void blswhstl_700300_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void ssriders_eeprom_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void ssriders_1c0300_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void tmnt_priority_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void tmnt_upd_start_w(uint8_t data);
	uint8_t tmnt_upd_busy_r();

	DECLARE_MACHINE_RESET(common);
	DECLARE_VIDEO_START(cuebrick);
	DECLARE_VIDEO_START(mia);
	DECLARE_MACHINE_RESET(tmnt);
	DECLARE_VIDEO_START(tmnt);
	DECLARE_VIDEO_START(lgtnfght);
	DECLARE_VIDEO_START(blswhstl);
	uint32_t screen_update_mia(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_tmnt(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_punkshot(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_lgtnfght(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_glfgreat(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_tmnt2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	uint32_t screen_update_thndrx2(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(screen_vblank_blswhstl);
	INTERRUPT_GEN_MEMBER(tmnt_interrupt);
	INTERRUPT_GEN_MEMBER(punkshot_interrupt);
	INTERRUPT_GEN_MEMBER(lgtnfght_interrupt);
	inline uint32_t tmnt2_get_word( uint32_t addr );
	void tmnt2_put_word( uint32_t addr, uint16_t data );
	void volume_callback(uint8_t data);
	K051960_CB_MEMBER(mia_sprite_callback);
	K051960_CB_MEMBER(tmnt_sprite_callback);
	K051960_CB_MEMBER(punkshot_sprite_callback);
	K051960_CB_MEMBER(thndrx2_sprite_callback);
	K05324X_CB_MEMBER(lgtnfght_sprite_callback);
	K05324X_CB_MEMBER(blswhstl_sprite_callback);
	K052109_CB_MEMBER(mia_tile_callback);
	K052109_CB_MEMBER(cuebrick_tile_callback);
	K052109_CB_MEMBER(tmnt_tile_callback);
	K052109_CB_MEMBER(ssbl_tile_callback);
	K052109_CB_MEMBER(blswhstl_tile_callback);
	SAMPLES_START_CB_MEMBER(tmnt_decode_sample);

	void blswhstl_main_map(address_map &map);
	void cuebrick_main_map(address_map &map);
	void lgtnfght_audio_map(address_map &map);
	void lgtnfght_main_map(address_map &map);
	void mia_audio_map(address_map &map);
	void mia_main_map(address_map &map);
	void punkshot_audio_map(address_map &map);
	void punkshot_main_map(address_map &map);
	void ssriders_audio_map(address_map &map);
	void ssriders_main_map(address_map &map);
	void sunsetbl_main_map(address_map &map);
	void thndrx2_audio_map(address_map &map);
	void thndrx2_main_map(address_map &map);
	void tmnt2_main_map(address_map &map);
	void tmnt_audio_map(address_map &map);
	void tmntucbl_audio_map(address_map &map);
	void tmnt_main_map(address_map &map);

	virtual void device_timer(emu_timer &timer, device_timer_id id, int param) override;
};

class glfgreat_state : public tmnt_state
{
public:
	glfgreat_state(const machine_config &mconfig, device_type type, const char *tag) :
		tmnt_state(mconfig, type, tag),
		m_analog_controller(*this, "CONTROL%c", 'A')
	{ }

	void glfgreat(machine_config &config);

private:
	void k053251_glfgreat_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint8_t controller_r();
	uint16_t glfgreat_rom_r(offs_t offset);
	void glfgreat_122000_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint16_t glfgreat_ball_r();
	void glfgreat_sound_w(offs_t offset, uint8_t data);

	TILE_GET_INFO_MEMBER(glfgreat_get_roz_tile_info);
	DECLARE_VIDEO_START(glfgreat);

	void glfgreat_audio_map(address_map &map);
	void glfgreat_main_map(address_map &map);

	required_ioport_array<4> m_analog_controller;

	uint8_t    m_controller_select = 0;
	int        m_roz_rom_bank = 0;
	int        m_roz_char_bank = 0;
	int        m_roz_rom_mode = 0;
};

class prmrsocr_state : public tmnt_state
{
public:
	prmrsocr_state(const machine_config &mconfig, device_type type, const char *tag) :
		tmnt_state(mconfig, type, tag)
	{ }

	void prmrsocr(machine_config &config);

protected:
	virtual void machine_start() override;

private:
	void prmrsocr_sound_irq_w(uint16_t data);
	void prmrsocr_audio_bankswitch_w(uint8_t data);
	void prmrsocr_eeprom_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	void prmrsocr_122000_w(offs_t offset, uint16_t data, uint16_t mem_mask = ~0);
	uint16_t prmrsocr_rom_r(offs_t offset);

	TILE_GET_INFO_MEMBER(prmrsocr_get_roz_tile_info);
	DECLARE_VIDEO_START(prmrsocr);
	K05324X_CB_MEMBER(prmrsocr_sprite_callback);

	void prmrsocr_audio_map(address_map &map);
	void prmrsocr_main_map(address_map &map);

	int        m_sprite_bank = 0;
	int        m_roz_char_bank = 0;
};

#endif // MAME_INCLUDES_TMNT_H
