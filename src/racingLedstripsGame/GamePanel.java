package racingLedstripsGame;

import java.awt.Graphics;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;
import javax.swing.JFrame;
import javax.swing.JPanel;

import racingLedstripsGame.Ledstrip;

@SuppressWarnings("serial")
public class GamePanel extends JPanel implements KeyListener {
	ArrayList<Ledstrip> ledstrips;

	public GamePanel() {
		ledstrips = new ArrayList<Ledstrip>();
		for (int i = 0; i < 2; i++) {
			Ledstrip A = new Ledstrip(35, 350 + 50 * i);
			ledstrips.add(A);
		}
	}

	public static void main(String[] args) throws InterruptedException {
		GamePanel gamepanel = new GamePanel();
		JFrame f = new JFrame();
		f.addKeyListener(gamepanel);
		f.setSize(1200, 500);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setTitle("Racing Leds");
		f.setLocation(150, 50);
		f.add(gamepanel);
		f.setVisible(true);
		f.setFocusable(true);
		f.requestFocus();
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		for (int i = 0; i < ledstrips.size(); i++) {
			ledstrips.get(i).DrawLedstrip(g);
		}
	}

	@Override
	public void addNotify() {
		super.addNotify();
		this.requestFocusInWindow();
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_SPACE) {
			if (ledstrips.get(0).LedstripOnOrOff() & ledstrips.get(0).LedstripOnOrOff()) {
				for (int i = 0; i < ledstrips.size(); i++) {
					ledstrips.get(i).initialize();
				}
				this.repaint();
				System.out.println("space button");
				System.out.println(ledstrips.get(0).OnOff);
				System.out.println(ledstrips.get(1).OnOff);
			}
		}

		if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
			ledstrips.get(0).update("R");
			this.repaint();
			System.out.println("right arrow");
			System.out.println(ledstrips.get(0).OnOff);
			System.out.println(ledstrips.get(1).OnOff);
		}

		if (e.getKeyCode() == KeyEvent.VK_LEFT) {
			ledstrips.get(0).update("L");
			this.repaint();
			System.out.println("left arrow");
			System.out.println(ledstrips.get(0).OnOff);
			System.out.println(ledstrips.get(1).OnOff);
		}

		if (e.getKeyCode() == KeyEvent.VK_C) {
			ledstrips.get(1).update("R");
			this.repaint();
			System.out.println("c");
			System.out.println(ledstrips.get(0).OnOff);
			System.out.println(ledstrips.get(1).OnOff);
		}

		if (e.getKeyCode() == KeyEvent.VK_W) {
			ledstrips.get(1).update("L");
			this.repaint();
			System.out.println("w");
			System.out.println(ledstrips.get(0).OnOff);
			System.out.println(ledstrips.get(1).OnOff);
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
	}
}
