object Form2: TForm2
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'VolumeWarning'
  ClientHeight = 374
  ClientWidth = 519
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
    Left = 82
    Top = 35
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object Image1: TImage
    Left = 84
    Top = 54
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
  object TrackBar1: TTrackBar
    Left = 40
    Top = 35
    Width = 36
    Height = 305
    Max = 100
    Orientation = trVertical
    Frequency = 50
    ShowSelRange = False
    TabOrder = 0
    TabStop = False
    ThumbLength = 25
  end
  object MediaPlayer1: TMediaPlayer
    Left = 216
    Top = 200
    Width = 253
    Height = 30
    EnabledButtons = [btPlay]
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 1
  end
end
