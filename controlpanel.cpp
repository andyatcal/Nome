/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "controlpanel.h"

ControlPanel::ControlPanel()
{
    setupLayout();
    //buildConnection();
}

ControlPanel::ControlPanel(SlideGLWidget * canvas)
{
    setupLayout();
    this -> canvas = canvas;
    buildConnection();
    resize(300, 600);
}

void ControlPanel::buildConnection()
{
    /* Build our connections. */
    connect(viewContent, SIGNAL(activated(int)), canvas, SLOT(viewContentChanged(int)));
    connect(mergeButton, SIGNAL(clicked(bool)), canvas, SLOT(mergeCalled(bool)));
    connect(mergeButton, SIGNAL(clicked(bool)), this, SLOT(pushMerge(bool)));
    connect(subdivLevelSlider,SIGNAL(valueChanged(int)), canvas, SLOT(levelChanged(int)));
    connect(subdivLevelSlider, SIGNAL(valueChanged(int)), this, SLOT(viewContentSetToSubdiv(int)));
    connect(resetViewButton, SIGNAL(clicked(bool)), canvas, SLOT(resetViewDirection(bool)));
    connect(minOffsetBox, SIGNAL(textChanged(QString)), this, SLOT(resetMinOffset(QString)));
    connect(maxOffsetBox, SIGNAL(textChanged(QString)), this, SLOT(resetMaxOffset(QString)));
    connect(offsetStepBox, SIGNAL(textChanged(QString)), this, SLOT(resetOffsetStep(QString)));
    connect(offsetValueSlider, SIGNAL(sliderReleased()), this, SLOT(offSetSliderMoved()));
    connect(this, SIGNAL(makeOffsetMesh(float)), canvas, SLOT(offsetValueChanged(float)));
    connect(foreColorButton, SIGNAL(clicked(bool)), this, SLOT(resetForeColor(bool)));
    connect(backColorButton, SIGNAL(clicked(bool)), this, SLOT(resetBackColor(bool)));
    connect(vertexModeButton, SIGNAL(clicked(bool)), this, SLOT(vertexModeChecked(bool)));
    connect(borderModeButton, SIGNAL(clicked(bool)), this, SLOT(borderModeChecked(bool)));
    connect(faceModeButton, SIGNAL(clicked(bool)), this, SLOT(faceModeChecked(bool)));
    connect(canvas, SIGNAL(feedback_status_bar(QString, int)), statusBar, SLOT(showMessage(QString,int)));
    connect(vertexModeButton, SIGNAL(clicked(bool)), canvas, SLOT(vertexModeChecked(bool)));
    connect(borderModeButton, SIGNAL(clicked(bool)), canvas, SLOT(borderModeChecked(bool)));
    connect(faceModeButton, SIGNAL(clicked(bool)), canvas, SLOT(faceModeChecked(bool)));
    connect(addFaceButton, SIGNAL(clicked(bool)), canvas, SLOT(addToTempCalled(bool)));
    connect(deleteFaceButton, SIGNAL(clicked(bool)), canvas, SLOT(deleteFaceCalled(bool)));
    connect(addBorderButton, SIGNAL(clicked(bool)), canvas, SLOT(addBorderCalled(bool)));
    connect(zipButton, SIGNAL(clicked(bool)), canvas, SLOT(zipToTempCalled(bool)));
    connect(clearSelectionButton,SIGNAL(clicked(bool)), canvas, SLOT(clearSelectionCalled(bool)));
    //connect(addTempToMasterButton, SIGNAL(clicked(bool)), canvas, SLOT(addTempToMasterCalled(bool)));
    connect(wholeBorderCheck,SIGNAL(clicked(bool)), canvas, SLOT(wholeBorderSelectionChecked(bool)));
    connect(trianglePaneltyEdit, SIGNAL(textChanged(QString)), canvas, SLOT(resetTrianglePanelty(QString)));
    connect(consolidateButton, SIGNAL(clicked(bool)), canvas, SLOT(consolidateTempMesh(bool)));
}

void ControlPanel::setupLayout()
{
    /* Main Layout.
     * Contains view, mode, subdivision, offset, color, status.*/
    setLayout(mainLayout = new QVBoxLayout);
    mainLayout -> setMargin(10);
    mainLayout->setSpacing(5);
    mainLayout -> addWidget(new QLabel("VIEW MODE"));
    mainLayout -> addLayout(viewLayout = new QVBoxLayout);
    mainLayout -> addWidget(new QLabel("EDIT MODE"));
    mainLayout -> addLayout(modeLayout = new QVBoxLayout);
    mainLayout -> addWidget(new QLabel("SUBDIVISION"));
    mainLayout -> addLayout(subdivLayout = new QVBoxLayout);
    mainLayout -> addWidget(new QLabel("OFFSET"));
    mainLayout -> addLayout(offsetLayout = new QVBoxLayout);
    mainLayout -> addWidget(new QLabel("COLOR"));
    mainLayout -> addLayout(colorLayout = new QVBoxLayout);
    /* View layout. */
    viewLayout -> addWidget(viewContent = new QComboBox);
    viewContent -> addItem("Hirachical Scene");
    viewContent -> addItem("Merged Mesh");
    viewContent -> addItem("Subdivision Mesh");
    viewContent -> addItem("Offset Mesh");
    viewContent -> addItem("Subdivision on Offset Mesh");
    viewContent -> setCurrentIndex(0);
    viewLayout -> addWidget(resetViewButton = new QPushButton(tr("Reset Arcball View")));

    /* Mode layout.*/
    modeLayout -> addLayout(selectionLayout = new QHBoxLayout);
    modeLayout -> addLayout(editLayout = new QHBoxLayout);
    modeLayout -> addLayout(zipOptionsLayout = new QHBoxLayout);
    selectionLayout -> addWidget(faceModeButton = new QRadioButton(tr("Select Face")));
    selectionLayout -> addWidget(vertexModeButton = new QRadioButton(tr("Select Vertex")));
    vertexModeButton -> setChecked(true);
    selectionLayout -> addWidget(borderModeButton = new QRadioButton(tr("Select Border")));
    editLayout -> addWidget(addFaceButton = new QPushButton(tr("Add Polygon")));
    editLayout -> addWidget(addBorderButton = new QPushButton(tr("Add One Border")));
    editLayout -> addWidget(deleteFaceButton = new QPushButton(tr("Delete Face")));
    zipOptionsLayout -> addWidget(new QLabel(tr("Triangle Panelty")));
    zipOptionsLayout -> addWidget(trianglePaneltyEdit = new QLineEdit(tr("1.3")));
    zipOptionsLayout -> addWidget(zipButton = new QPushButton(tr("Zip Two Mesh Borders")));
    modeLayout -> addLayout(addOrClearLayout = new QHBoxLayout);
    modeLayout-> addWidget(autoCorrectCheck = new QCheckBox(tr("Auto Correct Adding Face Oreinataion")));
    autoCorrectCheck -> setChecked(true);
    modeLayout-> addWidget(wholeBorderCheck = new QCheckBox(tr("Zip Whole Border Loop")));
    wholeBorderCheck -> setChecked(true);
    wholeBorderCheck -> setEnabled(false);
    //addOrClearLayout->addWidget(addTempToMasterButton = new QPushButton(tr("Add to Initial Mesh")));
    addOrClearLayout->addWidget(clearSelectionButton = new QPushButton(tr("Clear Selection")));
    modeLayout -> addWidget(consolidateButton = new QPushButton(tr("Consolidate Temp Mesh")));
    modeLayout -> addWidget(mergeButton = new QPushButton(tr("Merge All")));
    /* Subdivision layout. */
    subdivLayout -> addLayout(subdivLevelLayout = new QHBoxLayout);
    subdivLevelLayout -> addWidget(new QLabel("Level 0"));
    subdivLevelLayout -> addWidget(subdivLevelSlider = new QSlider(Qt::Horizontal));
    subdivLevelLayout -> addWidget(new QLabel("Level 5"));
    subdivLayout -> addWidget(currentLevelLabel = new QLabel(tr("Current Subdivision Level:    0")));
    subdivLevelSlider -> setMinimum(0);
    subdivLevelSlider -> setMaximum(5);
    subdivLevelSlider -> setValue(0);
    /* Offset Layout. */
    maxOffset = 0.005;
    minOffset = 0.001;
    offsetStep = 4;
    offsetLayout -> addLayout(offsetMinMaxLayout = new QHBoxLayout);
    offsetMinMaxLayout -> addWidget((new QLabel(tr("Min"))));
    offsetMinMaxLayout -> addWidget(minOffsetBox = new QLineEdit(QString::number(minOffset)));
    offsetMinMaxLayout -> addWidget((new QLabel(tr("Max"))));
    offsetMinMaxLayout -> addWidget(maxOffsetBox = new QLineEdit(QString::number(maxOffset)));
    offsetMinMaxLayout -> addWidget((new QLabel(tr("Step"))));
    offsetMinMaxLayout -> addWidget(offsetStepBox = new QLineEdit(QString::number(offsetStep)));
    offsetLayout -> addLayout(offsetValueLayout = new QHBoxLayout);
    offsetValueLayout -> addWidget(offsetValueSlider = new QSlider(Qt::Horizontal));
    offsetValueSlider -> setMinimum(0);
    offsetValueSlider -> setMaximum(offsetStep);
    offsetValueSlider -> setValue(0);
    offsetLayout -> addWidget(currentOffsetValueLabel = new QLabel(tr("Current Offset Value:    ")));
    /* Color Layout. */
    colorLayout -> addLayout(foreColorLayout = new QHBoxLayout);
    colorLayout -> addLayout(backColorLayout = new QHBoxLayout);
    colorLayout -> setSpacing(2);
    foreColorLayout -> addWidget(foreColorButton = new QPushButton(tr("Foreground Color")));
    foreColorLayout -> addWidget(foreColorBox = new QWidget());
    foreColorBox -> resize(5,5);
    QPalette forePal = foreColorBox->palette();
    forePal.setColor(foreColorBox->backgroundRole(), QColor(255,0,0));
    foreColorBox->setPalette(forePal);
    foreColorBox -> setAutoFillBackground(true);
    backColorLayout -> addWidget(backColorButton = new QPushButton(tr("Background Color")));
    backColorLayout -> addWidget(backColorBox = new QWidget());
    QPalette backPal = foreColorBox->palette();
    backPal.setColor(backColorBox->backgroundRole(), QColor(0,0,0));
    backColorBox->setPalette(backPal);
    backColorBox -> setAutoFillBackground(true);
    backColorBox -> resize(5,5);
    mainLayout -> addWidget(statusBar = new QStatusBar);
}

void ControlPanel::test(QString test)
{
    cout<<test.toStdString()<<endl;
}

void ControlPanel::test(bool checked)
{
    cout<<"Hello!"<<endl;
}

void ControlPanel::viewContentReset()
{
    viewContent ->setCurrentIndex(1);
}

void ControlPanel::viewContentSetToSubdiv(int level)
{
    viewContent -> setCurrentIndex(2);
    currentLevelLabel -> setText(tr("Current Subdivision Level:    "
                                    ) + QString::number(level));
}

void ControlPanel::resetMinOffset(QString minOffset)
{
    this->minOffset = minOffset.toFloat();
}

void ControlPanel::resetMaxOffset(QString maxOffset)
{
    this->maxOffset = maxOffset.toFloat();
}

void ControlPanel::resetOffsetStep(QString offsetStep)
{
    this->offsetStep = offsetStep.toInt();
    offsetValueSlider->setMaximum(this->offsetStep);
}

void ControlPanel::offSetSliderMoved()
{
    int value = offsetValueSlider ->value();
    float realOffsetValue = minOffset + (maxOffset - minOffset) / offsetStep * value;
    emit makeOffsetMesh(realOffsetValue);
    viewContent -> setCurrentIndex(3);
    currentOffsetValueLabel -> setText(tr("Current Offset Value:    "
                                          ) + QString::number(realOffsetValue));
}

void ControlPanel::viewContentSetToSubdivOffset()
{
    viewContent -> setCurrentIndex(4);
}

void ControlPanel::resetForeColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette forePal = foreColorBox->palette();
    forePal.setColor(foreColorBox->backgroundRole(), newColor);
    foreColorBox->setPalette(forePal);
    canvas -> setForeColor(newColor);
}

void ControlPanel::resetBackColor(bool)
{
    QColor newColor = QColorDialog::getColor();
    QPalette backPal = backColorBox->palette();
    backPal.setColor(backColorBox->backgroundRole(), newColor);
    backColorBox->setPalette(backPal);
    canvas -> setBackColor(newColor);
}

void ControlPanel::vertexModeChecked(bool checked)
{
    autoCorrectCheck->setEnabled(checked);
    wholeBorderCheck->setEnabled(!checked);
    statusBar -> showMessage(tr("Switch to Vertex Selection Mode"));
}

void ControlPanel::borderModeChecked(bool checked)
{
    autoCorrectCheck->setEnabled(!checked);
    wholeBorderCheck->setEnabled(checked);
    statusBar -> showMessage(tr("Switch to Border Selection Mode"));
}

void ControlPanel::faceModeChecked(bool checked)
{
    autoCorrectCheck->setEnabled(!checked);
    wholeBorderCheck->setEnabled(!checked);
    statusBar -> showMessage(tr("Switch to Face Selection Mode"));
}

void ControlPanel::pushMerge(bool)
{
    viewContent -> setCurrentIndex(1);
}
