﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Effekseer.GUI.Dock
{
	class LocationAbsValues : DockPanel
	{
		Component.ParameterList paramerterList = null;

		bool isFiestUpdate = true;

		public LocationAbsValues()
		{
			Label = Resources.GetString("AttractionForces") + "###AttractionForces";

			paramerterList = new Component.ParameterList();
			paramerterList.SetType(typeof(Data.LocationAbsValues));

			Core.OnAfterLoad += OnAfterLoad;
			Core.OnAfterNew += OnAfterLoad;
			Core.OnAfterSelectNode += OnAfterSelectNode;
			
			Read();

			Icon = Images.GetIcon("PanelLocationAbs");
			IconSize = new swig.Vec2(24, 24);
			TabToolTip = Resources.GetString("AttractionForces");
		}

		public void FixValues()
		{
			paramerterList.FixValues();
		}

		public override void OnDisposed()
		{
			FixValues();

			Core.OnAfterLoad -= OnAfterLoad;
			Core.OnAfterNew -= OnAfterLoad;
			Core.OnAfterSelectNode -= OnAfterSelectNode;
		}

		protected override void UpdateInternal()
		{
			if (isFiestUpdate)
			{
			}

			paramerterList.Update();
		}

		void Read()
		{
			if (Core.SelectedNode != null)
			{
				if (Core.SelectedNode is Data.Node)
				{
					paramerterList.SetValue(((Data.Node)Core.SelectedNode).LocationAbsValues);
				}
				else
				{
					paramerterList.SetValue(null);
				}
			}
			else
			{
				paramerterList.SetValue(null);
			}
		}

		void OnAfterLoad(object sender, EventArgs e)
		{
			Read();
		}

		void OnAfterSelectNode(object sender, EventArgs e)
		{
			Read();
		}
	}
}
