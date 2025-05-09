#ifndef __PC_KEYBOARD_H
#define __PC_KEYBOARD_H

/**
 * Initialize I2C keyboard when system started
 */
void pc_keyboard_init();

/**
 * Clean up I2C keyboard stuff
 */
void pc_keyboard_cleanup();

#endif /* __PC_KEYBOARD_H */
