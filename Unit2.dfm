object Form2: TForm2
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'VolumeWarning'
  ClientHeight = 339
  ClientWidth = 192
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 100
    Top = 8
    Width = 17
    Height = 13
    Alignment = taRightJustify
    Caption = 'Label1'
  end
  object Image1: TImage
    Left = 108
    Top = 43
    Width = 17
    Height = 276
    Picture.Data = {
      0954506E67496D61676589504E470D0A1A0A0000000D49484452000000110000
      0114080200000042B54AAA000000017352474200AECE1CE90000000467414D41
      0000B18F0BFC6105000000097048597300000EC300000EC301C76FA864000000
      494944415478DAEDCB31010000040030AAC8A3AC8632785CDBBFACE9384AC771
      1CC7711CC7711CC7711CC7711CC7711CC7711CC7711CC7711CC7711CC7711CC7
      711CC7711CC7715ECF02DCB236907C69C0390000000049454E44AE426082}
  end
  object Label2: TLabel
    Left = 45
    Top = 10
    Width = 18
    Height = 13
    Alignment = taRightJustify
    Caption = '100'
  end
  object labelFloor: TLabel
    Left = 377
    Top = 10
    Width = 17
    Height = 13
    Alignment = taRightJustify
    Caption = '0'
  end
  object labelCeiling: TLabel
    Left = 247
    Top = 54
    Width = 29
    Height = 13
    Caption = 'ceiling'
  end
  object TrackBar1: TTrackBar
    Left = 45
    Top = 29
    Width = 33
    Height = 302
    Max = 100
    Orientation = trVertical
    Frequency = 5
    ShowSelRange = False
    TabOrder = 1
    TabStop = False
    ThumbLength = 25
    OnChange = TrackBar1Change
  end
  object MediaPlayer1: TMediaPlayer
    Left = 464
    Top = 309
    Width = 253
    Height = 21
    EnabledButtons = [btPlay]
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 3
    TabStop = False
  end
  object sliderFloor: TTrackBar
    Left = 377
    Top = 29
    Width = 33
    Height = 302
    Max = 100
    Orientation = trVertical
    Frequency = 5
    Position = 100
    ShowSelRange = False
    TabOrder = 0
    TabStop = False
    OnChange = sliderFloorChange
  end
  object sliderCeiling: TTrackBar
    Left = 199
    Top = 43
    Width = 20
    Height = 302
    Max = 100
    Orientation = trVertical
    ShowSelRange = False
    TabOrder = 2
    TabStop = False
    OnChange = sliderCeilingChange
  end
end
