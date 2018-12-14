﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Resources;
using System.Threading;

using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;

namespace Effekseer
{
	/// <summary>
	/// 値が変化したときのイベント
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="e"></param>
	public delegate void ChangedValueEventHandler(object sender, ChangedValueEventArgs e);

	public enum ChangedValueType
	{ 
		Execute,
		Unexecute,
	}

	/// <summary>
	/// 値が変化したときのイベントの引数
	/// </summary>
	public class ChangedValueEventArgs : EventArgs
	{
		public object Value
		{
			get;
			private set;
		}

		public ChangedValueType Type
		{
			get;
			private set;
		}

		internal ChangedValueEventArgs(object value, ChangedValueType type)
		{
			Value = value;
			Type = type;
		}
	}

	/// <summary>
	/// 言語
	/// </summary>
	public enum Language
	{
        [Name(value = "日本語", language = Language.Japanese)]
        [Name(value = "Japanese", language = Language.English)]
		Japanese,
        [Name(value = "英語", language = Language.Japanese)]
        [Name(value = "English", language = Language.English)]
		English,
	}

    // アセンブリからリソースファイルをロードする
    // Resources.GetString(...) に介して取得する場合、
    // カルチャーによってローカライズ済の文字列が得られます。
    public static class Resources
    {
		/* this implementation causes errors in mono
		[DataContract]
		class Data
		{
			[DataMember]
			public Dictionary<string, string> kv;
		}
		*/

		static ResourceManager resources;

		static Dictionary<string, string> keyToStrings = new Dictionary<string, string>();

		static Resources()
        {
        }

		public static void SetResourceManager(ResourceManager resourceManager)
		{
			resources = resourceManager;
		}

		public static void LoadLanguageFile(string path)
		{
			var lines = System.IO.File.ReadAllLines(path);

			foreach(var line in lines)
			{
				var strs = line.Split(',');
				if (strs.Length < 2) continue;

				var key = strs[0];
				var value = string.Join(",", strs.Skip(1));
				value = value.Replace(@"\n", "\n");

				keyToStrings.Add(key, value);
			}

			/* this implementation causes errors in mono
			var bytes = System.IO.File.ReadAllBytes(path);
		
			var settings = new DataContractJsonSerializerSettings();
			settings.UseSimpleDictionaryFormat = true;
			var serializer = new DataContractJsonSerializer(typeof(Data), settings);
			using (var ms = new MemoryStream(bytes))
			{
				var data = (Data)serializer.ReadObject(ms);
				foreach (var x in data.kv)
				{
					keyToStrings = data.kv;
				}
			}
			*/
		}

		public static string GetString(string name)
        {
			if(keyToStrings.ContainsKey(name))
			{
				return keyToStrings[name];
			}

            if (resources == null) return string.Empty;
			
            try
            {
                var value = resources.GetString(name);
                if (!String.IsNullOrEmpty(value)) return value; // 発見した場合、文字列を返す
            }
            catch {}
            
            return string.Empty;
        }
    }

	/// <summary>
	/// 名称を設定する属性
	/// </summary>
	[AttributeUsage(
	AttributeTargets.Class | AttributeTargets.Property | AttributeTargets.Field | AttributeTargets.Method,
	AllowMultiple = true,
	Inherited = false)]
	public class NameAttribute : Attribute
	{
        static NameAttribute()
        {
        }

		public NameAttribute()
		{
			language = Language.English;
			value = string.Empty;
		}

		public Language language
		{
			get;
			set;
		}

		public string value
		{
			get;
			set;
		}

		/// <summary>
		/// 属性から名称を取得する。
		/// </summary>
		/// <param name="attributes"></param>
		/// <returns></returns>
		public static string GetName(object[] attributes)
		{
			if (attributes != null && attributes.Length > 0)
			{
				foreach (var attribute in attributes)
				{
					if (!(attribute is NameAttribute)) continue;

                    // 先にProperties.Resourcesから検索する
                    var value = Resources.GetString(((NameAttribute)attribute).value);
                    if (!String.IsNullOrEmpty(value)) return value; // 発見した場合、文字列を返す

                    // なければ、既存振る舞いで返す
					if (((NameAttribute)attribute).language == Core.Language)
					{
						return ((NameAttribute)attribute).value;
					}
				}
			}

			return string.Empty;
		}
	}

	/// <summary>
	/// 説明を設定する属性
	/// </summary>
	[AttributeUsage(
	AttributeTargets.Class | AttributeTargets.Property | AttributeTargets.Field,
	AllowMultiple = true,
	Inherited = false)]
	public class DescriptionAttribute : Attribute
	{
		public DescriptionAttribute()
		{
			language = Language.English;
			value = string.Empty;
		}

		public Language language
		{
			get;
			set;
		}

		public string value
		{
			get;
			set;
		}

		/// <summary>
		/// 属性から説明を取得する。
		/// </summary>
		/// <param name="attributes"></param>
		/// <returns></returns>
		public static string GetDescription(object[] attributes)
		{
			if (attributes != null && attributes.Length > 0)
			{
				foreach (var attribute in attributes)
				{
					if (!(attribute is DescriptionAttribute)) continue;

                    // 先にProperties.Resourcesから検索する
                    var value = Resources.GetString(((DescriptionAttribute)attribute).value);
                    if (!String.IsNullOrEmpty(value)) return value; // 発見した場合、文字列を返す

					if (((DescriptionAttribute)attribute).language == Core.Language)
					{
						return ((DescriptionAttribute)attribute).value;
					}
				}
			}

			return string.Empty;
		}
	}

	
	/// <summary>
	/// アイコンを設定する属性
	/// </summary>
	[AttributeUsage(
	AttributeTargets.Class | AttributeTargets.Property | AttributeTargets.Field | AttributeTargets.Method,
	AllowMultiple = true,
	Inherited = false)]
	public class IconAttribute : Attribute
	{
		public IconAttribute()
		{
			resourceName = string.Empty;
		}

		public string resourceName
		{
			get;
			set;
		}
		
		/// <summary>
		/// アイコン属性を探す。
		/// </summary>
		/// <param name="attributes"></param>
		/// <returns></returns>
		public static IconAttribute GetIcon(object[] attributes)
		{
			if (attributes != null && attributes.Length > 0)
			{
				foreach (var attribute in attributes)
				{
					if (!(attribute is IconAttribute)) continue;

					return (IconAttribute)attribute;
				}
			}

			return null;
		}
	}

	public class Setting
	{
		public static System.Globalization.NumberFormatInfo NFI
		{
			get;
			private set;
		}

		static Setting()
		{
			var culture = new System.Globalization.CultureInfo("ja-JP");
			NFI = culture.NumberFormat;
		}
	}
}
