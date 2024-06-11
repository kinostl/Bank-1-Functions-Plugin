const id = "BANK_1_MANIP_PLUGIN_CALL_BANK_1_WIN_EVENT"
const groups = ["EVENT_GROUP_SCREEN"]
const name = "Call Bank 1 Overlay Event"

MAX_STACK_SIZE = 8

const fields = [
  {
    key: "funName",
    label: "Bank 1 Function",
    type: "select",
    options: [
      ["setWinTileColor", "Set Tile Color"],
      ["flipWinTileX", "Flip Tile Horizontal"],
      ["flipWinTileY", "Flip Tile Vertical"],
      ["drawWinTileOverObjects", "Draw Over Actors"],
      ["drawWinTileUnderObjects", "Draw Under Actors"],
      ["rotateWinTile", "Rotate Tile"],
      ["incrementWinTileColor", "Increment Tile Color"],
      ["decrementWinTileColor", "Decrement Tile Color"],
    ],
    defaultValue: "setWinTileColor"
  },
  {
    key: `coordX`,
    label: `X`,
    type: "union",
    types: ["number", "variable"],
    defaultType: "number",
      defaultValue: {
        number: 0,
        variable: "LAST_VARIABLE",
      },
      width: "50%"
  },
  {
    key: `coordY`,
    label: `Y`,
    type: "union",
    types: ["number", "variable"],
    defaultType: "number",
      defaultValue: {
        number: 0,
        variable: "LAST_VARIABLE",
      },
      width: "50%"
  },
  {
    label: 'Overlays start with their tiles set to display over objects',
    conditions: [
      {
        key: "funName",
        in: ["drawWinTileOverObjects", "drawWinTileUnderObjects"]
      }
    ]
  },
  {
    label: 'Every shade except for the lightest one will draw over the actors going under it.\nThis option will have no effect if you do not activate Sprites Over Window first.',
    conditions: [
      {
        key: "funName",
        in: ["drawWinTileOverObjects", "drawWinTileUnderObjects"]
      }
    ]
  },
  {
    label: 'Use a GBVM event with "VM_SET_CONST_UINT8 _show_actors_on_overlay, 1" to do this',
    conditions: [
      {
        key: "funName",
        in: ["drawWinTileOverObjects", "drawWinTileUnderObjects"]
      }
    ]
  },
  {
    label: 'Rotate Tile actually works via flip x and flip y. This usually results in an effect similar to rotation, but may not rotate certain tile types.',
    conditions: [
      {
        key: "funName",
        eq: "rotateWinTile"
      }
    ]
  },
  {
    label: 'Background Tile Number',
    key: 'tileColor',
    type: 'togglebuttons',
    options: [
      [0, '1'],
      [1, '2'],
      [2, '3'],
      [3, '4'],
      [4, '5'],
      [5, '6'],
      [6, '7'],
      [7, '8'],
    ],
    conditions: [
      {
        key: "funName",
        eq: "setWinTileColor"
      } 
    ]
  }
]

const compile = (input, helpers) => {
  const { 
    _callNative,
    _stackPushConst,
    _stackPush,
    _stackPop,
    getActorIndex,
    getVariableAlias,
    _addComment,
    scene,
    options
  } = helpers
  
  let stackSize = 2;
  
  const pushUnion = (union) => {
    switch(union.type){
      case "number":
        _stackPushConst(union.value)
        break;
      case "variable":
        _stackPush(getVariableAlias(union.value))
        break;
    }
  }
  
  if(input.funName == "setWinTileColor") {
    _stackPushConst(input["tileColor"])
    stackSize++;
  }
  
  pushUnion(input["coordX"])
  pushUnion(input["coordY"])
  
  _callNative(input.funName)
  
  _stackPop(stackSize)
}

module.exports = {
  id,
  name,
  groups,
  fields,
  compile,
}
