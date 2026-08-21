import hashlib
import json
from pathlib import Path

folder = Path(__file__).parent

mapping = {
    "textures": {},
    "musics": {},
    "sound_buffers": {}
}

rename_list = []

for file in folder.iterdir():
    if not file.is_file():
        continue

    suffix = file.suffix

    if suffix in {".jpg", ".png"}:
        category = "textures"
    elif suffix == ".mp3":
        category = "musics"
    elif suffix == ".MP3":
        category = "sound_buffers"
    else:
        continue

    # 原文件名，不包含扩展名
    original_name = file.stem

    # 检查同一类别中是否存在重复 ID
    if original_name in mapping[category]:
        raise RuntimeError(
            f"发现重复 ID：{category}/{original_name}"
        )

    # 对原文件名进行 SHA-256
    hashed_name = hashlib.sha256(
        original_name.encode("utf-8")
    ).hexdigest()

    target = folder / hashed_name

    # 防止覆盖已有文件
    if target.exists():
        raise RuntimeError(
            f"目标文件已存在：{target.name}"
        )

    mapping[category][original_name] = hashed_name
    rename_list.append((file, target))


# 所有文件检查完成后，再执行重命名
for source, target in rename_list:
    source.rename(target)
    print(f"{source.name} -> {target.name}")


# 输出 JSON
json_path = folder / "manifest.json"

with json_path.open("w", encoding="utf-8") as f:
    json.dump(
        mapping,
        f,
        ensure_ascii=False,
        indent=4
    )

print()
print(f"完成，共处理 {len(rename_list)} 个文件")
print(f"映射文件：{json_path}")