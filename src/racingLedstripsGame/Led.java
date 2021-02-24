package racingLedstripsGame;

import java.awt.Color;
import java.awt.Graphics;

public class Led {
	// appearance
	int side;
	int r;

	// position
	int xpos;
	int ypos;

	// used colors
	Color black = new Color(0, 0, 0);
	Color grey = new Color(128, 128, 128);
	Color yellow = new Color(255, 255, 0);
	Color OnOff;

	public Led(int side, int r, int xpos, int ypos) {
		// appearance
		this.side = side;
		this.r = r;
		// position
		this.xpos = xpos;
		this.ypos = ypos;
		// colors
		this.OnOff = grey;
	}

	public void DrawLed(Graphics g) {
		g.setColor(black);
		g.drawRect(xpos, ypos, side, side);
		g.drawOval(xpos, ypos, r, r);
		g.setColor(OnOff);
		g.fillOval(xpos, ypos, r, r);
	}

	public void LedOn() {
		OnOff = yellow;
	}

	public void LedOff() {
		OnOff = grey;
	}
}
