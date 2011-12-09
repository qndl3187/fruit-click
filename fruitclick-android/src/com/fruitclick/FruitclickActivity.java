package com.fruitclick;

import android.os.Bundle;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.backends.android.AndroidApplication;
import com.badlogic.gdx.graphics.GL10;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.g2d.TextureRegion;

public class FruitclickActivity extends AndroidApplication {
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		initialize(new Application(), false);
	}
}

class Application implements ApplicationListener, InputProcessor {

	private SpriteBatch batch;
	private Texture texture;
	private TextureRegion background;
	private TextureRegion apple;
	private BitmapFont font;

	private Sound crunch;
	private Sound crash;

	private native void createNative();

	private native void disposeNative();

	private native void renderNative();

	private native void touchNative(int x, int y);

	static {
		System.loadLibrary("fruitclick");
	}

	public void create() {
		batch = new SpriteBatch();
		texture = new Texture(Gdx.files.internal("images/texture.png"));
		background = new TextureRegion(texture, 0, 0, 320, 480);
		apple = new TextureRegion(texture, 320, 0, 50, 50);
		font = new BitmapFont();
		font.setColor(0, 0, 0, 1);

		crunch = Gdx.audio.newSound(Gdx.files.internal("sounds/crunch.wav"));
		crash = Gdx.audio.newSound(Gdx.files.internal("sounds/crash.wav"));
		Gdx.input.setInputProcessor(this);

		createNative();
	}

	public void dispose() {
		disposeNative();
		batch.dispose();
		texture.dispose();
		font.dispose();
		crunch.dispose();
		crash.dispose();
	}

	public void render() {
		renderNative();
	}

	public void resize(int w, int h) {
	}

	public void pause() {
	}

	public void resume() {
	}

	public boolean keyDown(int keycode) {
		return false;
	}

	public boolean keyUp(int keycode) {
		return false;
	}

	public boolean keyTyped(char character) {
		return false;
	}

	public boolean touchDown(int x, int y, int pointer, int button) {
		touchNative(x, Gdx.graphics.getHeight() - y);
		return false;
	}

	public boolean touchUp(int x, int y, int pointer, int button) {
		return false;
	}

	public boolean touchDragged(int x, int y, int pointer) {
		return false;
	}

	public boolean touchMoved(int x, int y) {
		return false;
	}

	public boolean scrolled(int amount) {
		return false;
	}

	public void drawBegin() {
		Gdx.gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
		batch.begin();
	}

	public void drawEnd() {
		batch.end();
	}

	private final int APPLE = 0;
	private final int BACKGROUND = 1;

	public void draw(int id, float x, float y, float angle) {
		TextureRegion region = null;
		switch (id) {
		case BACKGROUND:
			region = background;
			break;
		case APPLE:
			region = apple;
			break;
		default:
			break;
		}

		float w = region.getRegionWidth();
		float h = region.getRegionHeight();

		batch.draw(region, x - w / 2, y - h / 2, w / 2, h / 2, w, h, 1, 1,
				angle);
	}

	public void drawText(String text, float x, float y) {
		font.draw(batch, text, x, y);
	}

	private final int CRUNCH = 0;
	private final int CRASH = 1;

	public void playSound(int id) {
		switch (id) {
		case CRUNCH:
			crunch.play();
			break;
		case CRASH:
			crash.play();
			break;
		}
	}
}
