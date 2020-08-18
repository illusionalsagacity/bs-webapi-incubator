type t = Dom.htmlFormControlsCollection;

type t_namedItem = [
  | `RadioNodeList(Dom.radioNodeList)
  | `Button(Dom.htmlButtonElement)
  | `Fieldset(Dom.htmlFieldSetElement)
  | `Input(Dom.htmlInputElement)
  | `Object(Dom.htmlObjectElement)
  | `Output(Dom.htmlOutputElement)
  | `Select(Dom.htmlSelectElement)
  | `Textarea(Dom.htmlTextAreaElement)
];

include Webapi__Dom__HtmlCollection.Impl({ type nonrec t = t; });

let isRadioNodeList: 'a => bool = [%raw {|
  function(x) { return x instanceof RadioNodeList; }
|}];

[@bs.send] [@bs.return nullable] external _namedItem: (t, string) => option('a) = "namedItem";
let namedItem = (t, string) =>
  switch (_namedItem(t, string)) {
  | Some(el) =>
    if (Webapi__Dom__RadioNodeList.unsafeAsRadioNodeList(el)->isRadioNodeList) {
      el->Obj.magic->`RadioNodeList->Some;
    } else {
      switch (Webapi__Dom__Element.tagName(el)) {
      // fixme: this should be a classify function in Webapi__Dom__HtmlElement
      | "button" => el->Obj.magic->`Button->Some
      | "fieldset" => el->Obj.magic->`Fieldset->Some
      | "input" => el->Obj.magic->`Input->Some
      | "object" => el->Obj.magic->`Object->Some
      | "output" => el->Obj.magic->`Output->Some
      | "select" => el->Obj.magic->`Select->Some
      | "textarea" => el->Obj.magic->`Textarea->Some
      | _ => None
      };
    }
  | None => None
  };
