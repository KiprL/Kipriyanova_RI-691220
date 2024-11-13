object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 475
  ClientWidth = 831
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 24
    Top = 72
    Width = 272
    Height = 15
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1073#1091#1082#1074#1091' '#1090#1086#1084#1072' '#1080#1083#1080' '#1074#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1086#1073#1088#1072#1079#1072'....'
  end
  object Button1: TButton
    Left = 40
    Top = 144
    Width = 97
    Height = 25
    Caption = #1042#1099#1073#1088#1072#1090#1100' '#1092#1072#1081#1083
    TabOrder = 0
    OnClick = Button1Click
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 360
    Top = 53
    Width = 449
    Height = 380
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = -1
    Header.MainColumn = 1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 1
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'ID'
      end
      item
        Position = 1
        Text = #1055#1091#1090#1100'/'#1044#1080#1089#1082
        Width = 100
      end
      item
        Position = 2
        Text = #1056#1072#1089#1096#1080#1088#1077#1085#1080#1077' '#1092#1072#1081#1083#1072
        Width = 150
      end
      item
        Position = 3
        Text = #1053#1086#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072
        Width = 145
      end>
  end
  object Edit1: TEdit
    Left = 24
    Top = 99
    Width = 305
    Height = 23
    Enabled = False
    TabOrder = 2
    Text = #1055#1088#1080#1084#1077#1088': C'
    OnKeyPress = Edit1KeyPress
  end
  object Button2: TButton
    Left = 112
    Top = 360
    Width = 105
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 3
    OnClick = Button2Click
  end
  object RadioGroup1: TRadioGroup
    Left = 24
    Top = 200
    Width = 257
    Height = 105
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1088#1072#1089#1096#1080#1088#1077#1085#1080#1077' '#1092#1072#1081#1083#1086#1074' '#1076#1083#1103' '#1087#1086#1080#1089#1082#1072
    Items.Strings = (
      'EXE'
      'PDF'
      'ZIP'
      'DEB')
    TabOrder = 4
  end
  object Button3: TButton
    Left = 200
    Top = 144
    Width = 112
    Height = 25
    Caption = #1042#1074#1077#1089#1090#1080' '#1073#1091#1082#1074#1091' '#1090#1086#1084#1072
    TabOrder = 5
    OnClick = Button3Click
  end
end
