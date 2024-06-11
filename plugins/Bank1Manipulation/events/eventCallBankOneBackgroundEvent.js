const id = "BANK_1_MANIP_PLUGIN_CALL_BANK_1_BKG_EVENT"
const groups = ["EVENT_GROUP_SCREEN"]
const name = "Call Bank 1 Background Event"

MAX_STACK_SIZE = 8

const fields = [
  {
    key: "funName",
    label: "Bank 1 Function",
    type: "select",
    options: [
      ["setBkgTileColor", "Set Tile Color"],
      ["flipBkgTileX", "Flip Tile Horizontal"],
      ["flipBkgTileY", "Flip Tile Vertical"],
      ["drawOverObjects", "Draw Over Actors"],
      ["drawUnderObjects", "Draw Under Actors"],
      ["rotateBkgTile", "Rotate Tile"],
      ["incrementBkgTileColor", "Increment Tile Color"],
      ["decrementBkgTileColor", "Decrement Tile Color"],
    ],
    defaultValue: "setBkgTileColor"
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
    types: ["number", "variable", "actor"],
    defaultType: "number",
      defaultValue: {
        number: 0,
        variable: "LAST_VARIABLE",
      },
      width: "50%"
  },
  {
    label: 'Every shade except for the lightest one will draw over the actors going under it.',
    conditions: [
      {
        key: "funName",
        eq: "drawOverObjects"
      }
    ]
  },
  {
    label: 'Rotate Tile actually works via flip x and flip y. This usually results in an effect similar to rotation, but may not rotate certain tile types.',
    conditions: [
      {
        key: "funName",
        eq: "rotateBkgTile"
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
        eq: "setBkgTileColor"
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
  
  if(input.funName == "setBkgTileColor") {
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
