std::string wrapText(const std::string& input, sf::Font& font, unsigned int charSize, float maxWidth) {
    std::string result;
    std::string word;
    std::istringstream stream(input);
    sf::Text testText;
    testText.setFont(font);
    testText.setCharacterSize(charSize);

    float currentLineWidth = 0.f;

    while (stream >> word) {
        std::string nextWord = word + " ";
        testText.setString(result + nextWord);

        float width = testText.getLocalBounds().width;
        if (width > maxWidth) {
            result += "\n" + nextWord;
        } else {
            result += nextWord;
        }
    }

    return result;
}
