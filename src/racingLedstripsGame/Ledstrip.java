package racingLedstripsGame;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;

public class Ledstrip {
	public ArrayList<Led> ledstrip;
	int length;
	Color grey = new Color(128, 128, 128);
	List<Integer> OnOff;

	public Ledstrip(int length, int ypos) {
		this.length = length;
		ledstrip = new ArrayList<Led>();
		OnOff = new ArrayList<Integer>();
		for (int i = 0; i < length; i++) {
			Led A = new Led(30, 30, 50 + 30 * i, ypos);
			ledstrip.add(A);
			OnOff.add(0);
		}
	}

	public void DrawLedstrip(Graphics g) {
		for (int i = 0; i < ledstrip.size(); i++) {
			if (OnOff.get(i) == 1) {
				ledstrip.get(i).LedOn();
				ledstrip.get(i).DrawLed(g);
			}
			if (OnOff.get(i) == 0) {
				ledstrip.get(i).LedOff();
				ledstrip.get(i).DrawLed(g);

			}
		}
	}

	public void update(String RL) {
		boolean indexfound = false;
		int index = 0;
		while (indexfound == false) {
			for (int i = 0; i < OnOff.size(); i++) {
				if (OnOff.get(i) == 1) {
					index = i;
					indexfound = true;
					OnOff.set(index, 0);
				}
			}
			if (RL == "R") {
				if (index + 1 <= OnOff.size() - 1) {
					OnOff.set(index + 1, 1);
				} else {
					OnOff.set(0, 1);
				}
			}
			if (RL == "L") {
				if (index - 1 < 0) {
					OnOff.set(OnOff.size() - 1, 1);
				} else {
					OnOff.set(index - 1, 1);
				}
			}
		}

	}

	public void initialize() {
		ledstrip.get(0).LedOn();
		OnOff.set(0, 1);
	}

	public boolean LedstripOnOrOff() {
		boolean OnorOff = true;
		for (int i = 0; i<ledstrip.size(); i++) {
			if(OnOff.get(i) == 1) {
				OnorOff = false;
			}
		}
		return OnorOff;
	}
}
