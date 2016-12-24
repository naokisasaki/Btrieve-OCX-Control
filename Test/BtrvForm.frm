VERSION 5.00
Object = "{36F63C00-ADE4-11D0-918D-444553540000}#1.0#0"; "Btrieve.ocx"
Begin VB.Form BtrvForm 
   Caption         =   "Btrieve/OCX Test"
   ClientHeight    =   4560
   ClientLeft      =   912
   ClientTop       =   1284
   ClientWidth     =   7644
   LinkTopic       =   "Form1"
   PaletteMode     =   1
   ScaleHeight     =   4560
   ScaleWidth      =   7644
   Begin VB.CommandButton Command2 
      Caption         =   "Other"
      Height          =   252
      Left            =   2880
      TabIndex        =   6
      Top             =   180
      Width           =   672
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Quit"
      Height          =   252
      Left            =   6780
      TabIndex        =   4
      Top             =   180
      Width           =   732
   End
   Begin VB.CommandButton Go 
      Caption         =   "Find"
      Height          =   252
      Left            =   2100
      TabIndex        =   3
      Top             =   180
      Width           =   672
   End
   Begin VB.ListBox List1 
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   9
         Charset         =   128
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3108
      Left            =   60
      TabIndex        =   2
      Top             =   600
      Width           =   7512
   End
   Begin VB.TextBox Text1 
      Height          =   264
      Left            =   960
      TabIndex        =   1
      Top             =   180
      Width           =   1032
   End
   Begin BTRIEVELib.Btrieve Btr1 
      Left            =   4260
      Top             =   120
      _Version        =   65536
      _ExtentX        =   656
      _ExtentY        =   656
      _StockProps     =   0
      Status          =   0
   End
   Begin VB.Label Label2 
      BackStyle       =   0
      Caption         =   $"BtrvForm.frx":0000
      ForeColor       =   &H00800000&
      Height          =   552
      Left            =   60
      TabIndex        =   5
      Top             =   3960
      Width           =   5652
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "ZIP"
      Height          =   180
      Left            =   180
      TabIndex        =   0
      Top             =   180
      Width           =   720
   End
End
Attribute VB_Name = "BtrvForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    End
End Sub


Private Sub Command2_Click()
    Dim Cnt As Integer
    Dim rv As Long
    
    
    rv = Btr1.Open("d:\projects\btrieve\test\ziptbl")
    
    If rv = True Then
        Btr1.GetEqual Format(Text1.Text, "@@@@@@!")
        
        While Btr1.Status = 0 And Cnt < 5
            Btr1.PutFieldValue "NAME", 999999
            Btr1.Update
            
            Btr1.GetNext
            
            Cnt = Cnt + 1
        
        Wend
        
        Btr1.Close
    End If

End Sub


Private Sub Go_Click()
    Dim Cnt As Integer
    Dim rv As Long
    
    List1.Clear
    
    rv = Btr1.Open("d:\projects\btrieve\test\ziptbl")
    
    If rv = True Then
        Btr1.GetEqual Format(Text1.Text, "@@@@@@!")
        
        While Btr1.Status = 0 And Cnt < 50
            List1.AddItem Format(Btr1.GetStringField(0), "@@@@@@  ") + _
                          Btr1.GetFieldValue("NAME")
        
            Btr1.GetNext
            
            Cnt = Cnt + 1
        
        Wend
        
        Btr1.Close
    End If
    
End Sub


