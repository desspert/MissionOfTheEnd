#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "SceneManager/SceneManager.h"
#include "cinder/Timeline.h"
class MainProject : public ci::app::AppNative {
private:
	SceneManager scene;
	float delta_time;
public:
	void prepareSettings(Settings* settings);
	void setup();
	void mouseMove(ci::app::MouseEvent event) override;
	void mouseDrag(ci::app::MouseEvent event) override;
	void mouseDown(ci::app::MouseEvent event) override;
	void mouseUp(ci::app::MouseEvent event) override;
	void update();
	void keyDown(ci::app::KeyEvent event) override;
	void keyUp(ci::app::KeyEvent event) override;
	void draw();
};

void MainProject::prepareSettings(Settings* settings) {
	settings->setWindowSize(1500, 1000);
	settings->disableFrameRate();
	hideCursor();
}

void MainProject::setup()
{
	scene.setup();
	ci::gl::enableAlphaBlending();
}

void MainProject::mouseMove(ci::app::MouseEvent event)
{
	scene.mouseMove(event);

}
void MainProject::mouseDrag(ci::app::MouseEvent event)
{
	scene.mouseMove(event);
}

void MainProject::mouseDown(ci::app::MouseEvent event)
{
	scene.mouseDown(event);
}

void MainProject::keyUp(ci::app::KeyEvent event) {
	scene.keyUp(event);
}

void MainProject::keyDown(ci::app::KeyEvent event) {
	scene.keyDown(event);
}
void MainProject::mouseUp(ci::app::MouseEvent event)
{
	scene.mouseUp(event);
}
void MainProject::update()
{
	delta_time = std::abs(delta_time - timeline().getCurrentTime());
	scene.update(delta_time);
	delta_time = timeline().getCurrentTime();
}

void MainProject::draw()
{
	scene.draw();
}



CINDER_APP_NATIVE( MainProject, ci::app::RendererGl )

