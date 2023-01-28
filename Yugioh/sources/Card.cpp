#include "headers/Card.h"
#include "headers/CardMenu.h"
#include <iostream>
#include <iterator>
#include <numeric>
Card::Card(const std::string& cardName, CardType cardType, CardLocation cardLocation,
           const std::string& cardDescription, std::string imagePath)
    : imagePath(imagePath), cardName(cardName), cardType(cardType), cardLocation(cardLocation),
      cardDescription(cardDescription) {
  QPixmap pixmap;
  pixmap.load(QString::fromStdString(imagePath));
  pixmap =
      pixmap.scaled(QSize(200, 150), Qt::KeepAspectRatio); // pixmap size needs to not be hardcoded
  height = pixmap.height();
  width = pixmap.width();
  setPixmap(pixmap);
  setAcceptHoverEvents(true);
  this->setZValue(-9);
  //    imagePath.clear();
  //    imagePath = nullptr;
}

Card::~Card() = default;

void Card::addToScene(QGraphicsScene* scene) {
  scene->addItem(this);
  scene->addWidget(cardMenu);
}

void Card::flipCard() {
  if (faceUp == true) {
    QPixmap pixmap;
    pixmap.load(QString::fromStdString(":/resources/pictures/card_back.jpg"));
    pixmap = pixmap.scaled(QSize(200, 150), Qt::KeepAspectRatio);
    setPixmap(pixmap);
    faceUp = false;
  } else {
    QPixmap pixmap;
    pixmap.load(QString::fromStdString(imagePath));
    pixmap = pixmap.scaled(QSize(200, 150), Qt::KeepAspectRatio);
    setPixmap(pixmap);
    faceUp = true;
  }
}

const std::map<MonsterPosition, QString> Card::monsterPositionEnumToQString{
    {MonsterPosition::ATTACK, "ATTACK"},
    {MonsterPosition::FACE_UP_DEFENSE, "FACE_UP_DEFENSE"},
    {MonsterPosition::FACE_DOWN_DEFENSE, "FACE_DOWN_DEFENSE"},
    {MonsterPosition::NONE, "NONE"}};

const std::map<SpellTrapPosition, QString> Card::spellTrapPositionEnumToQString{
    {SpellTrapPosition::FACE_UP, "FACE_UP"},
    {SpellTrapPosition::SET, "SET"},
    {SpellTrapPosition::NONE, "NONE"}};

const std::map<QString, MonsterPosition> Card::monsterPositionQStringToEnum{
    {"ATTACK", MonsterPosition::ATTACK},
    {"FACE_UP_DEFENSE", MonsterPosition::FACE_UP_DEFENSE},
    {"FACE_DOWN_DEFENSE", MonsterPosition::FACE_DOWN_DEFENSE},
    {"NONE", MonsterPosition::NONE}};

const std::map<QString, SpellTrapPosition> Card::spellTrapPositionQStringToEnum{
    {"FACE_UP", SpellTrapPosition::FACE_UP},
    {"SET", SpellTrapPosition::SET},
    {"NONE", SpellTrapPosition::NONE}};

auto Card::getCardName() const -> const std::string& { return cardName; }

auto Card::getCardType() const -> CardType { return cardType; }

auto Card::getCardLocationString() const -> std::string {
  switch (cardLocation) {
  case CardLocation::HAND:
    return "hand";
  case CardLocation::DECK:
    return "deck";
  case CardLocation::GRAVEYARD:
    return "graveyard";
  case CardLocation::FIELD:
    return "field";
  default:
    return "error:unsupported card location";
  }
}

auto Card::getIsActivated() const -> bool { return this->isActivated; }

auto Card::getPlayerThatSetThisCard() const -> int { return playerThatSetThisCard; }

auto Card::getIsSetThisTurn() const -> bool { return this->isSetThisTurn; }

auto Card::getCardLocation() const -> CardLocation { return cardLocation; }

auto Card::getCardTypeString() const -> std::string {
  switch (cardType) {
  case CardType::MONSTER_CARD:
    return "monster card";
  case CardType::TRAP_CARD:
    return "trap card";
  case CardType::SPELL_CARD:
    return "spell card";
  default:
    return "error: unsupported card type";
  }
}

void Card::setCardLocation(CardLocation newCardLocation) { cardLocation = newCardLocation; }

void Card::setIsActivated(bool isActivated) { this->isActivated = isActivated; }

void Card::setPlayerThatSetThisCard(int playerNumber) {
  this->playerThatSetThisCard = playerNumber;
}

void Card::setIsSetThisTurn(bool isSetThisTurn) { this->isSetThisTurn = isSetThisTurn; }

auto Card::getCardDescription() const -> const std::string& { return cardDescription; }

auto Card::operator==(const Card& other) const -> bool {
  return this->getCardName() == other.getCardName();
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
  // TODO: Is this even possible since QGraphicsPixmapItem doesn't inherit QObject
  emit cardHoveredEnter(*this);
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) { emit cardHoveredLeave(*this); }

void Card::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {}

void Card::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  std::cout << "Card " << this->getCardName() << " was clicked!" << std::endl;
  if (event->buttons() & Qt::LeftButton) {
    emit cardSelected(this);
  }
}

void Card::move(float x, float y) {
  setPos(x, y); // we need to implement a unified move() function that moves the card and the menu
                // at the same time
  cardMenu->move(pos().x(), pos().y() - cardMenu->height());
  cardMenu->hide();
}

void Card::setName(std::string name) { cardName = name; }

auto Card::getHeight() -> float { return height; }

auto Card::getWidth() -> float { return width; }

auto operator<<(std::ostream& out, Card& c) -> std::ostream& {
  return out << "Card name: " << c.getCardName() << ", card type: " << c.getCardTypeString()
             << ",card location: " << c.getCardLocationString()
             << ",card description: " << c.getCardDescription() << std::endl;
}
