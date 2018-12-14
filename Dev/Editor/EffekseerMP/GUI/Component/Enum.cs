﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Effekseer.GUI.Component
{
	class Enum : Control, IParameterControl
	{
		string id = "";

		public string Label { get; set; } = string.Empty;

		public string Description { get; set; } = string.Empty;

		Data.Value.EnumBase binding = null;

		int[] enums = null;

		public List<string> FieldNames = new List<string>();
		
		List<swig.ImageResource> icons = new List<swig.ImageResource>();

		public bool EnableUndo { get; set; } = true;

		int selectedValues = -1;
		string preview_value = string.Empty;
		bool isInitialized = false;

		public Data.Value.EnumBase Binding
		{
			get
			{
				return binding;
			}
			set
			{
				if (binding == value) return;

				binding = value;

				if (binding != null)
				{
					selectedValues = binding.GetValueAsInt();
				}
			}
		}

		public void Initialize(Type enumType)
		{
			if (isInitialized) return;
			isInitialized = true;

			// to avoid to change placesGetValues, use  GetFields
			var list = new List<int>();
			var fields = enumType.GetFields();
			//var iconBitmaps = new List<Bitmap>();
			//bool hasIcon = false;

			foreach (var f in fields)
			{
				if (f.FieldType != enumType) continue;

				var attributes = f.GetCustomAttributes(false);
				var name = NameAttribute.GetName(attributes);
				if (name == string.Empty)
				{
					name = f.ToString();
				}
				
				var iconAttribute = IconAttribute.GetIcon(attributes);
				swig.ImageResource icon = null;
				if (iconAttribute != null)
				{
					icon = Images.GetIcon(iconAttribute.resourceName);
				}

				list.Add((int)f.GetValue(null));
				FieldNames.Add(name);
				icons.Add(icon);
			}
			enums = list.ToArray();
		}

		public Enum(string label = null)
		{
			if (label != null)
			{
				Label = label;
			}

			id = "###" + Manager.GetUniqueID().ToString();
		}

		public void SetBinding(object o)
		{
			var o_ = o as Data.Value.EnumBase;
			Binding = o_;
		}

		public void FixValue()
		{
		}

		public override void Update()
		{
			if (binding != null)
			{
				selectedValues = binding.GetValueAsInt();
			}
			else
			{
				selectedValues = -1;
			}

			var v = enums.Select((_, i) => Tuple.Create(_, i)).Where(_ => _.Item1 == selectedValues).FirstOrDefault();

			if(Manager.NativeManager.BeginCombo(id, FieldNames[v.Item2], swig.ComboFlags.None, icons[v.Item2]))
			{
				for(int i = 0; i < FieldNames.Count; i++)
				{
					bool is_selected = (FieldNames[v.Item2] == FieldNames[i]);

					if (Manager.NativeManager.Selectable(FieldNames[i], is_selected, swig.SelectableFlags.None, icons[i]))
					{
						selectedValues = enums[i];
						binding.SetValue(selectedValues);
					}
						
					if (is_selected)
					{
						Manager.NativeManager.SetItemDefaultFocus();
					}

				}

				Manager.NativeManager.EndCombo();
			}
		}
	}
}
