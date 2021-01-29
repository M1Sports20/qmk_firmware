/* Copyright 2021 Michael Spradling <mike@mspradling.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <spi_master.h>
#include <qp.h>
#include <qp_internal.h>
#include <qp_sh1106.h>
#include <qp_ssd_internal.h>

static ssd_painter_device_t drivers[SH1106_NUM_DEVICES] = {0};

painter_device_t qp_sh1106_spi_make_device(pin_t chip_select_pin, pin_t data_pin, pin_t reset_pin, uint16_t spi_divisor, bool uses_backlight)
{
    for (uint32_t i = 0; i < SH1106_NUM_DEVICES; i++) {
	ssd_painter_device_t *driver = &drivers[i];
	memset(driver, 0, sizeof(ssd_painter_device_t));
	if (!driver->allocated) {
	    driver->allocated           = true;
	    //driver->qp_driver.init      = qp_ili9488_init;
	    //driver->qp_driver.clear     = qp_ili9xxx_clear;
	    //driver->qp_driver.power     = qp_ili9xxx_power;
	    //driver->qp_driver.pixdata   = qp_ili9xxx_pixdata;
	    //driver->qp_driver.viewport  = qp_ili9xxx_viewport;
	    //driver->qp_driver.setpixel  = qp_ili9xxx_setpixel;
	    //driver->qp_driver.line      = qp_ili9xxx_line;
	    //driver->qp_driver.rect      = qp_ili9xxx_rect;
	    //driver->qp_driver.circle    = qp_fallback_circle;
	    //driver->qp_driver.ellipse   = qp_fallback_ellipse;
	    //driver->qp_driver.drawimage = qp_ili9xxx_drawimage;
	    driver->bus                 = QP_BUS_SPI;
	    driver->chip_select_pin     = chip_select_pin;
	    driver->data_pin            = data_pin;
	    driver->reset_pin           = reset_pin;
	    driver->spi_divisor         = spi_divisor;
	    return (painter_device_t)driver;
	}
    }
    return NULL;
}
