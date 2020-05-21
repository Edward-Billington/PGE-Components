#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class GameBar {
private:
    int height, width, scale, pos_x, pos_y;
    float progress;
    olc::Pixel fill_colour, border_colour;
    std::string text;
    bool display_text;

public:
    /**
     * Default Constructor, these are default values which can be modified with various public methods.
     */
    GameBar() {
        this->scale = 8;
        this->height = 16;
        this->width = this->height * this->scale;
        this->pos_x = 0;
        this->pos_y = 0;
        this->fill_colour = olc::GREEN;
        this->border_colour = olc::WHITE;
        this->progress = 0.1f;
        this->display_text = false;
        this->text = std::string("PLACEHOLDER");
    }

    /**
     * Set the height of the bar, the width is automatically calculated using the scale so that it scales consistently.
     *
     * @param h, the height of the bar.
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& SetHeight(int h) {
        // Disallow height values under 2 as it causes graphical glitches.
        if (h <= 1)
            return *this;

        this->height = h;
        this->width = h * this->scale;
        return *this;
    }

    /**
     * Set the location of the top-left pixel, everything is draw down and right of this value.
     *
     * @param loc, a PGE 2D vector for screen position.
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& SetLocation(const olc::vi2d& loc) {
        this->pos_x = loc.x;
        this->pos_y = loc.y;
        return *this;
    }

    /**
     * Set the colour of the filled bar.
     *
     * @param c, a PGE Colour value.
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& SetBarColour(const olc::Pixel &c) {
        this->fill_colour = c;
        return *this;
    }

     /**
      * Set the colour of the bar's border.
      *
      * @param c, a PGE Colour value.
      * @return a reference to the GameBar object, this is to allow chaining of method calls.
      */
    GameBar& SetBorderColour(const olc::Pixel &c) {
        this->border_colour = c;
        return *this;
    }

     /**
      * Set the percentage of the bar to be filled.
      *
      * @param p, value from 0.0 to 1.0 or 0% to 100% filled.
      * @return a reference to the GameBar object, this is to allow chaining of method calls.
      */
    GameBar& SetProgress(float p) {
        if (p > 1.0f)
            this->progress = 1.0f;
        else if (p < 0.0f)
            this->progress = 0.0f;
        else
            this->progress = p;
        return *this;
    }

    /**
     * Increase the percentage of the bar filled.
     *
     * @param p, value to be added to the current percentage.
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& IncreaseProgress(float p) {
        if (p < 0.0f)
            return *this;

        if (this->progress + p > 1.0f)
            this->progress = 1.0f;
        else
            this->progress += p;

        return *this;
    }

    /**
     * Decrease the percentage of the bar filled.
     *
     * @param p, value to be removed from the current percentage.
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& DecreaseProgress(float p) {
        if (p < 0.0f)
            return *this;

        if (this->progress - p < 0.0f)
            this->progress = 0.0f;
        else
            this->progress -= p;

        return *this;
    }

    /**
     * Hides or shows the text about the bar, according to the boolean input.
     *
     * @param b, boolean value to either display or hide the text above the bar.
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& DisplayText(bool b) {
        this->display_text = b;
        return *this;
    }

    /**
     * Set the string to display above the bar.
     *
     * @param title
     * @return a reference to the GameBar object, this is to allow chaining of method calls.
     */
    GameBar& SetText(const std::string &title) {
        this->text = title;
        return *this;
    }

    /**
     * Draws the bar on the screen.
     *
     * @param pge, this must be passed in to access PGE methods.
     * More detail on that in the docs: https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/Multiple-File-Projects
     */
    void Draw(olc::PixelGameEngine* pge) {
        pge->DrawRect(this->pos_x, this->pos_y, this->width, this->height, this->border_colour);
        pge->FillRect(this->pos_x + 1, this->pos_y + 1, ((float)(this->width - 1) * this->progress), this->height - 1, this->fill_colour);
        if(this->display_text && (this->height / 16) != 0)
            pge->DrawString(this->pos_x - (this->height/16)+2, this->pos_y - ((this->height/16) * 8), this->text, olc::WHITE, this->height / 16);
    }
};