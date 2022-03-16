#pragma once

enum button_States { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font{};
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;
		sf::Color buttonIdleColor;
		sf::Color buttonHoverColor;
		sf::Color buttonActiveColor;


	public:
		Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size, sf::Color buttonIdleColor, sf::Color buttonHoverColor, sf::Color buttonActiveColor, sf::Color textIdleColor = sf::Color::White, sf::Color textHoverColor = sf::Color::White, sf::Color textActiveColor = sf::Color::White, short unsigned id = 0);
		~Button();

		//Accessors
		const bool isActive() const;
		const std::string getText() const;
		const int getIndexOfList(std::string list[], int len, std::string seek);
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);


		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class Slider
	{
	private:
		//Variables
		sf::Font& font;
		gui::Button* activeElement;
		gui::Button* rightButton;
		gui::Button* leftButton;

		int listSize;
		std::string list[50];

		float keytime;
		float keytimeMax;

		//Private functions



	public:
		//Constructors and destructors
		Slider(float x, float y, float height, sf::Font& font, std::string list[], int list_size);
		~Slider();


		//Accessors
		const bool getKeytime();
		const unsigned short getActiveElementId() const;

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);
	};

}


