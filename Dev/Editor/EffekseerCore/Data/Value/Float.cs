﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Effekseer.Utl;

namespace Effekseer.Data.Value
{
	public class Float
	{
		float _value = 0;
		float _max = float.MaxValue;
		float _min = float.MinValue;
		
		public float Value
		{
			get
			{
				return GetValue();
			}

			set
			{
				SetValue(value);
			}
		}

		/// <summary>
		/// 変更単位量
		/// </summary>
		public float Step
		{
			get;
			set;
		}

		public float RangeMin
		{
			get { return _min; }
		}

		public float RangeMax
		{
			get { return _max; }
		}

		internal float DefaultValue { get; private set; }

		public event ChangedValueEventHandler OnChanged;

		internal Float(float value = 0, float max = float.MaxValue, float min = float.MinValue, float step = 1.0f)
		{
			_max = max;
			_min = min;
			_value = value.Clipping(_max, _min);
			Step = step;
			DefaultValue = _value;
		}

		protected void CallChanged(object value, ChangedValueType type)
		{
			if (OnChanged != null)
			{
				OnChanged(this, new ChangedValueEventArgs(value, type));
			}
		}

		public float GetValue()
		{
			return _value;
		}

		public void SetValue(float value, bool isCombined = false)
		{
			value = value.Clipping(_max, _min);

			if (value == _value) return;

			float old_value = _value;
			float new_value = value;

			var cmd = new Command.DelegateCommand(
				() =>
				{
					_value = new_value;

					CallChanged(new_value, ChangedValueType.Execute);
				},
				() =>
				{
					_value = old_value;

					CallChanged(old_value, ChangedValueType.Unexecute);
				},
				this,
				isCombined);

			Command.CommandManager.Execute(cmd);
		}

		public void SetValueDirectly(float value)
		{
			var converted = value.Clipping(_max, _min);
			if (_value == converted) return;
			_value = converted;

			CallChanged(_value, ChangedValueType.Execute);
		}

		public static implicit operator float(Float value)
		{
			return value._value;
		}

		public static explicit operator byte[](Float value)
		{
			byte[] values = new byte[sizeof(float) * 1];
			BitConverter.GetBytes(value.Value).CopyTo(values, sizeof(float) * 0);
			return values;
		}

		public byte[] GetBytes(float mul = 1.0f)
		{
			byte[] values = new byte[sizeof(float) * 1];
			BitConverter.GetBytes(Value * mul).CopyTo(values, sizeof(float) * 0);
			return values;
		}
	}
}
